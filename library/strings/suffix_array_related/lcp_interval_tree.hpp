/** @file */
#pragma once
#include "../../monotonic_stack_related/min_cartesian_tree.hpp"
#include "suffix_array.hpp"
#include "lcp_array.hpp"
/**
 * @see https://citeseerx.ist.psu.edu /viewdoc/download?doi=10.1.1.88.1129
 * offline version of suffix tree
 * @code{.cpp}
 *     string s;
 *     lcp_tree lcpt(s, 256);
 *     // or
 *     vector<int> arr;
 *     lcp_tree lcpt(arr, 100'005);
 * @endcode
 */
template <class T> struct lcp_tree {
    T s;
    suf sf;
    vector<int> lcp, le, ri;
    int root;
    vector<map<int, int>> child;
    /**
     * @param a_s,max_val string/array with 0 <= s[i] < max_val
     * @time O((n log n) + max_val); besides suffix array construction, this is
     * O(n) as constructing a map from a sorted array is linear
     * @space all member variables are O(n)
     */
    lcp_tree(const T& a_s, int max_val) : s(a_s), sf(get_sa(s, max_val)), lcp(get_lcp_array(sf, s)) {
        tie(le, ri) = min_range(lcp);
        vector<vector<int>> adj;
        tie(root, adj) = min_cartesian_tree(le, ri, lcp);
        if (root == -1) return;
        child.resize(ssize(adj));
        queue<int> q({root});
        int num_leaves = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vector<pair<int, int>> childs;
            if (adj[u].empty() || le[u] < le[adj[u][0]]) {
                num_leaves++;
                int i = le[u] + 1;
                assert(sf.sa[i] + lcp[u] <= ssize(s));
                if (sf.sa[i] + lcp[u] < ssize(s))
                    childs.emplace_back(s[sf.sa[i] + lcp[u]], ssize(lcp) + i);
            }
            int prev = le[u] + 2;
            for (int v : adj[u]) {
                for (int i = prev; i <= le[v]; i++) {
                    assert(sf.sa[i] + lcp[u] < ssize(s));
                    childs.emplace_back(s[sf.sa[i] + lcp[u]], ssize(lcp) + i);
                    num_leaves++;
                }
                childs.emplace_back(s[sf.sa[v] + lcp[u]], v);
                prev = ri[v] + 1;
                q.push(v);
            }
            for (int i = prev; i <= ri[u]; i++) {
                assert(sf.sa[i] + lcp[u] < ssize(s));
                childs.emplace_back(s[sf.sa[i] + lcp[u]], ssize(lcp) + i);
                num_leaves++;
            }
            for (int i = 1; i < ssize(childs); i++) assert(childs[i - 1].first < childs[i].first);
            child[u] = map(begin(childs), end(childs));
        }
        assert(num_leaves == ssize(s));
    }
    /**
     * performs trie-style downwards tree walk
     * @param t needle
     * @returns range [le, ri) such that:
     * - for all i in [le, ri): t == s.substr(sf.sa[i], ssize(t))
     * - `ri - le` is the # of matches of t in s.
     * @time O(|t| * log(|alphabet|)); |alphabet| = 26 if only lowercase letters
     * @space O(1)
     */
    pair<int, int> find_str(const T& t) const {
        if (root == -1) {
            assert(ssize(sf.sa) <= 1);
            if (t.empty() || s == t) return {0, ssize(s)};
            return {0, 0};
        }
        assert(ssize(sf.sa) >= 2);
        int u = root;
        for (int i = 0; i < ssize(t); i++) {
            if (i == lcp[u]) {
                auto it = child[u].find(t[i]);
                if (it == end(child[u])) return {0, 0};
                u = it->second;
            }
            if (u >= ssize(lcp)) {
                int idx = u - ssize(lcp);
                auto it = mismatch(begin(t) + i, end(t), begin(s) + sf.sa[idx] + i, end(s)).first;
                return {idx, idx + (it == end(t))};
            }
            if (s[sf.sa[u] + i] != t[i]) return {0, 0};
        }
        return {le[u] + 1, ri[u] + 1};
    }
};
