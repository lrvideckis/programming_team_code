/** @file */
#pragma once
#include "../../../monotonic_stack_related/min_cartesian_tree.hpp"
#include "../suffix_array.hpp"
#include "../lcp_array.hpp"
/**
 * @see https://citeseerx.ist.psu.edu /viewdoc/download?doi=10.1.1.88.1129
 * offline version of suffix tree
 * @code{.cpp}
 *     string s;
 *     lcp_tree lt(s, 256);
 *     // or
 *     vector<int> arr;
 *     lcp_tree lt(arr, 100'005);
 *
 *     // same as DFS over suffix tree
 *     auto dfs = [&](auto&& self, int u) -> void {
 *         auto [le, ri] = lt.sa_range(u);
 *         int len = lt.lcp_len(u);
 *         if (u < ssize(lt.lcp))
 *             for(auto [c, v] : lt.child[u])
 *                 self(self, v);
 *     };
 *     dfs(dfs, max(lt.root, 0));
 * @endcode
 *
 * internal nodes are a subset of [1, n - 1)
 * leaf nodes are [n - 1, 2 * n - 1), each leaf represents a single suffix
 */
template <class T> struct lcp_tree {
    T s;
    vector<int> sa, sa_inv, lcp, le, ri;
    int root;
    vector<map<int, int>> child;
    /**
     * @param a_s,max_val string/array with 0 <= s[i] < max_val
     * @time O((n log n) + max_val); besides suffix array construction, this is
     * O(n) as constructing a map from a sorted array is linear
     * @space all member variables are O(n)
     */
    lcp_tree(const T& a_s, int max_val) : s(a_s) {
        tie(sa, sa_inv) = get_sa(s, max_val);
        lcp = get_lcp_array(sa, sa_inv, s);
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
                assert(sa[i] + lcp[u] <= ssize(s));
                if (sa[i] + lcp[u] < ssize(s))
                    childs.emplace_back(s[sa[i] + lcp[u]], ssize(lcp) + i);
            }
            int prev = le[u] + 2;
            for (int v : adj[u]) {
                for (int i = prev; i <= le[v]; i++) {
                    assert(sa[i] + lcp[u] < ssize(s));
                    childs.emplace_back(s[sa[i] + lcp[u]], ssize(lcp) + i);
                    num_leaves++;
                }
                childs.emplace_back(s[sa[v] + lcp[u]], v);
                prev = ri[v] + 1;
                q.push(v);
            }
            for (int i = prev; i <= ri[u]; i++) {
                assert(sa[i] + lcp[u] < ssize(s));
                childs.emplace_back(s[sa[i] + lcp[u]], ssize(lcp) + i);
                num_leaves++;
            }
            for (int i = 1; i < ssize(childs); i++) assert(childs[i - 1].first < childs[i].first);
            child[u] = map(begin(childs), end(childs));
        }
        assert(num_leaves == ssize(s));
    }
    /**
     * @param u node
     * @returns range [le, ri) such that the following (ri - le) substrings are equal:
     *     - for all i in [le, ri): s.substr(sa[i], lcp_len(u))
     * @time O(1)
     * @space O(1)
     */
    pair<int, int> sa_range(int u) const {
        if (u < ssize(lcp)) return {le[u] + 1, ri[u] + 1};
        int idx = u - ssize(lcp);
        return {idx, idx + 1};
    }
    /**
     * @param u node
     * @returns length of longest common prefix of u's interval
     * @time O(1)
     * @space O(1)
     */
    int lcp_len(int u) const {
        return u < ssize(lcp) ? lcp[u] : ssize(s) - sa[u - ssize(lcp)];
    }
};
