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
 * @endcode
 *
 * internal nodes are a subset of [1, n - 1)
 * leaf nodes are [n - 1, 2 * n - 1), each leaf represents a single suffix
 */
struct lcp_tree {
    int n, root;
    vector<int> sa, sa_inv, lcp, le, ri;
    vector<vector<int>> adj;
    /**
     * @param s string/array
     * @time O((n log n) + (n * len) + max_val)
     * @space adj is O(n * len)
     */
    lcp_tree(const string& s) : n(ssize(s)), adj(max(n - 1, 0), vector(len, -1)) {
        tie(sa, sa_inv) = get_sa(s, mn + len);
        lcp = get_lcp_array(sa, sa_inv, s);
        auto [a_root, a_adj, a_le, a_ri, to_min] = min_cartesian_tree(lcp);
        root = max(a_root, 0), le = a_le, ri = a_ri;
        for (int u = 0; u < n - 1; u++)
            for (int v : a_adj[u])
                adj[u][s[sa[v] + lcp[u]] - mn] = v;
        for (int i = 0; i < n; i++) {
            int prev_lcp = (i ? lcp[i - 1] : -1);
            int next_lcp = (i < n - 1 ? lcp[i] : 0);
            int u = (prev_lcp < next_lcp) ? i : to_min[i - 1];
            int idx = sa[i] + max(prev_lcp, next_lcp);
            if (u == n - 1 || idx == n) continue;
            adj[u][s[idx] - mn] = n - 1 + i;
        }
    }
    /**
     * @param u node
     * @returns range [le, ri) such that the following (ri - le) substrings are equal:
     *     - for all i in [le, ri): s.substr(sa[i], lcp_len(u))
     * @time O(1)
     * @space O(1)
     */
    array<int, 2> sa_range(int u) const {
        return u < n - 1 ? {le[u] + 1, ri[u] + 1} :
               {u - n + 1, u - n + 2};
    }
    /**
     * @param u node
     * @returns length of longest common prefix of u's interval
     * @time O(1)
     * @space O(1)
     */
    int lcp_len(int u) const {
        return u < n - 1 ? lcp[u] : n - sa[u - n + 1];
    }
    /**
     * @param u node
     * @param c letter (don't subtract mn)
     * @returns child of u following edge with label c, -1 means child doesn't exist
     * @time O(1)
     * @space O(1)
     */
    int get_child(int u, char c) const {
        return u < n - 1 ? adj[u][c - mn] : -1;
    }
};
