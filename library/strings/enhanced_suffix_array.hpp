/** @file */
#pragma once
#include "suffix_array.hpp"
#include "../data_structures/sparse_table.hpp"
#include "../monotonic_stack_related/min_cartesian_tree.hpp"
/**
 * Various queries you can do based on suffix array.
 */
template <typename T> struct enhanced_sa {
    T s;
    suffix_array<T> info;
    RMQ<int> rmq_lcp, rmq_sa;
    vector<int> le, ri;
    int root;
    vector<map<int, int>> lcp_tree;
    /**
     * @param a_s,max_val string/array with 0 <= a_s[i] < max_val
     * @time O((n log n) + max_val)
     * @space O(n log n) for RMQ's; O(max_val) for `freq` array used
     * temporarily in suffix_array constructor
     */
    enhanced_sa(const T& a_s, int max_val) :
        s(a_s),
        info(suffix_array(s, max_val)),
        rmq_lcp(info.lcp, [](int i, int j) -> int {return min(i, j);}),
        rmq_sa(info.sa, [](int i, int j) -> int {return min(i, j);}),
        lcp_tree(ssize(info.lcp)) {
        tie(le, ri) = get_range(info.lcp);
        vector<vector<int>> adj;
        tie(root, adj) = min_cartesian_tree(info.lcp, le, ri);
        assert(ssize(adj) == ssize(info.lcp));
        if (root == -1) return; //TODO: try to find a way to not special case this
        queue<int> q({root});
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            int prev = le[u] + 1;
            for (int v : adj[u]) {
                for (int i = prev; i <= le[v]; i++)
                    assert(lcp_tree[u].emplace(s[info.sa[i] + info.lcp[u]], ssize(s) + i).second);
                assert(lcp_tree[u].emplace(s[info.sa[v] + info.lcp[u]], v).second);
                prev = ri[v] + 1;
                q.push(v);
            }
            for (int i = prev; i <= ri[u]; i++)
                assert(lcp_tree[u].emplace(s[info.sa[i] + info.lcp[u]], ssize(s) + i).second);
        }
    }
    /**
     * @param idx1,idx2 starting 0-based-indexes of suffixes
     * @returns max integer k such that s.substr(idx1, k) == s.substr(idx2, k)
     * @time O(1)
     * @space O(1)
     */
    inline int get_lcp(int idx1, int idx2) const {
        if (idx1 == idx2) return ssize(s) - idx1;
        auto [x, y] = minmax(info.rank[idx1], info.rank[idx2]);
        return rmq_lcp.query(x, y);
    }
    /**
     * @param idx1,idx2 starting 0-based-indexes of suffixes
     * @returns 1 iff suffix s.substr(idx1) < s.substr(idx2)
     * @time O(1)
     * @space O(1)
     */
    inline bool less(int idx1, int idx2) const {
        return info.rank[idx1] < info.rank[idx2];
    }
    /**
     * @see https://github.com/yosupo06/Algorithm/blob /master/src/string/suffixarray.hpp
     * @param t needle
     * @returns range [le, ri) such that:
     * - for all i in [le, ri): t == s.substr(info.sa[i], ssize(t))
     * - `ri - le` is the # of matches of t in s.
     * @time O(|t| * log(|s|))
     * @space O(1)
     */
    pair<int, int> find(const T& t) const {
        if (root == -1) { //TODO: find a way to not have to special case this
            assert(ssize(info.sa) <= 1);
            return (ssize(t) == 1 && s == t) ? pair(0, 1) : pair(0, 0);
        }
        assert(ssize(info.sa) >= 2);
        int u = root;
        for (int i = 0, u = root; i < ssize(t); i++) {
            if (u < ssize(s) && i == info.lcp[u]) {
                auto it = lcp_tree[u].find(t[i]);
                if (it == end(lcp_tree[u])) return {0, 0};
                u = it->second;
            }
            if (s[info.sa[u % ssize(s)] + i] != t[i]) return {0, 0};
        }
        return u < ssize(s) ? pair(le[u] + 1, ri[u] + 1) : pair(u - ssize(s), u - ssize(s) + 1);
    }
    /**
     * @param t needle
     * @returns min i such that t == s.substr(i, ssize(t)) or -1. For example,
     * replace RMQ with kth-smallest PST/Wavelet to solve
     * https://open.kattis.com/problems /anothersubstringqueryproblem
     * @time O(|t| * log(|s|))
     * @space O(1)
     */
    int find_first(const T& t) const {
        auto [x, y] = find(t);
        if (x == y) return -1;
        return rmq_sa.query(x, y);
    }
};
