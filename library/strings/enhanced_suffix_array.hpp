/** @file */
#pragma once
#include "suffix_array.hpp"
#include "../monotonic_stack_related/min_cartesian_tree.hpp"
/**
 * @see https://citeseerx.ist.psu.edu /viewdoc/download?doi=10.1.1.88.1129
 * offline version of suffix tree
 */
template <typename T> struct enhanced_sa {
    T s;
    suffix_array<T> info;
    vector<int> le, ri;
    int root;
    vector<map<int, int>> child;
    /**
     * @param a_s,max_val string/array with 0 <= a_s[i] < max_val
     * @time O((n log n) + max_val)
     * @space O(n) for all member arrays; O(max_val) for `freq` array used
     * temporarily in suffix_array constructor
     */
    enhanced_sa(const T& a_s, int max_val) :
        s(a_s),
        info(suffix_array(s, max_val)),
        child(ssize(info.lcp)) {
        tie(le, ri) = get_range(info.lcp);
        vector<vector<int>> adj;
        tie(root, adj) = min_cartesian_tree(info.lcp, le, ri);
        if (root == -1) return;
        queue<int> q({root});
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            int prev = le[u] + 1;
            for (int v : adj[u]) {
                for (int i = prev; i <= le[v]; i++)
                    assert(child[u].emplace(s[info.sa[i] + info.lcp[u]], ssize(s) + i).second);
                assert(child[u].emplace(s[info.sa[v] + info.lcp[u]], v).second);
                prev = ri[v] + 1;
                q.push(v);
            }
            for (int i = prev; i <= ri[u]; i++)
                assert(child[u].emplace(s[info.sa[i] + info.lcp[u]], ssize(s) + i).second);
        }
    }
    /**
     * performs trie-style downwards tree walk
     * @param t needle
     * @returns range [le, ri) such that:
     * - for all i in [le, ri): t == s.substr(info.sa[i], ssize(t))
     * - `ri - le` is the # of matches of t in s.
     * @time O(|t| * log(|alphabet|)); |alphabet| = 26 if only lowercase letters
     * @space O(1)
     */
    pair<int, int> find(const T& t) const {
        if (root == -1) {
            assert(ssize(info.sa) <= 1);
            return (ssize(t) == 1 && s == t) ? pair(0, 1) : pair(0, 0);
        }
        assert(ssize(info.sa) >= 2);
        int u = root;
        for (int i = 0; i < ssize(t); i++) {
            if (i == info.lcp[u]) {
                auto it = child[u].find(t[i]);
                if (it == end(child[u])) return {0, 0};
                u = it->second;
            }
            if (u >= ssize(s)) {
                int idx = u - ssize(s);
                auto it = mismatch(begin(t) + i, end(t), begin(s) + info.sa[idx] + i, end(s)).first;
                return {idx, idx + (it == end(t))};
            }
            if (s[info.sa[u] + i] != t[i]) return {0, 0};
        }
        return {le[u] + 1, ri[u] + 1};
    }
};
