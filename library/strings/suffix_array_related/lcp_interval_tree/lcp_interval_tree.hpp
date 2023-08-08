/** @file */
#pragma once
#include "../../../monotonic_stack_related/min_cartesian_tree.hpp"
#include "../suffix_array.hpp"
#include "../lcp_array.hpp"
const int mn = '0', len = 75; // lower case letters and digits
/**
 * @see Replacing suffix trees with enhanced suffix arrays by Mohamed Ibrahim
 * Abouelhoda, Stefan Kurtz, Enno Ohlebusch
 *
 * offline version of suffix tree
 * @code{.cpp}
 *     string s;
 *     lcp_tree lt(s, 256);
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
struct lcp_tree {
    int n, root;
    string s;
    vector<int> sa, sa_inv, lcp, le, ri;
    vector<array<int, len>> child;
    /**
     * @param a_s,max_val string/array with 0 <= s[i] < max_val
     * @time O((n log n) + (n * len) + max_val)
     * @space child is O(n * len)
     */
    lcp_tree(const string& a_s, int max_val) : n(ssize(a_s)), s(a_s) {
        tie(sa, sa_inv) = get_sa(s, max_val);
        lcp = get_lcp_array(sa, sa_inv, s);
        tie(le, ri) = min_range(lcp);
        vector<vector<int>> adj;
        vector<int> to_min;
        tie(root, adj, to_min) = min_cartesian_tree(le, ri, lcp);
        if (root == -1) return;
        array<int, len> init;
        fill(begin(init), end(init), -1);
        child.resize(ssize(adj), init);
        for (int u = 0; u < ssize(adj); u++)
            for (int v : adj[u])
                child[u][s[sa[v] + lcp[u]] - mn] = v;
        for (int i = 0; i < n; i++) {
            int prev_lcp = (i ? lcp[i - 1] : 0);
            int next_lcp = (i < ssize(lcp) ? lcp[i] : 0);
            int idx = sa[i] + max(prev_lcp, next_lcp);
            if (idx == n) continue;
            int u = prev_lcp < next_lcp ? i : to_min[i - 1];
            child[u][s[idx] - mn] = ssize(lcp) + i;
        }
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
        return u < ssize(lcp) ? lcp[u] : n - sa[u - ssize(lcp)];
    }
    /**
     * @param u node
     * @param c letter (don't subtract mn)
     * @returns child of u following edge with label c, -1 means child doesn't exist
     * @time O(1)
     * @space O(1)
     */
    int get_child(int u, char c) const {
        return u < ssize(child) ? child[u][c - mn] : -1;
    }
};
