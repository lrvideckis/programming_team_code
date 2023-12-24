/** @file */
#pragma once
#include "../../../monotonic_stack_related/cartesian_tree.hpp"
#include "../suffix_array.hpp"
#include "../lcp_array.hpp"
const int mn = '0', max_val = 75; // mn <= s[i] < mn + max_val; for lowercase letters: mn = 'a', max_val = 26
/**
 * @see Replacing suffix trees with enhanced suffix arrays by Mohamed Ibrahim
 * Abouelhoda, Stefan Kurtz, Enno Ohlebusch
 *
 * offline version of suffix tree, idea: min cartesian tree of LCP array
 * corresponds exactly to the internal nodes of the suffix tree. Then add in
 * <= n nodes, one for each suffix, and it corresponds to the suffix tree.
 *
 * string = "cabcabacaabc"
 *                                              c
 *              c                               b
 *              b               c               a
 *              a               b           c   a
 *      c       a               a           b   c
 *      b       c       c       a           a   a
 *      a       a   c   b       c           a   b
 *      a       b   b   a       a       c   c   a
 *  c   c       a   a   a       b       b   a   c
 *  b   a   c | c   a   c       a       a   b | b
 *  a   b | b | b   c   a   c | c       a | a | a
 *  a | a | a | a | a   b | b | b   c | c | c | c
 *    1   2   3   1   0   1   2   0   1   2   3   <- LCP
 * (------------------------------R--------------)
 * (--------------a--) (--b------) (--c----------)
 * (a) (--b------) (c) (a) (--c--)     (--a------)
 *     (a) (--c--)             (a)     (a) (--b--)
 *             (a)                         (a) (c)
 *
 * note leaf nodes don't exist when that suffix is a prefix of a longer suffix
 *
 * @code{.cpp}
 *     string s;
 *     lcp_tree lt(s, 256);
 * @endcode
 *
 * internal nodes are a subset of [0, n - 1), each internal node represents:
 *     - a prefix of some suffix; in the suffix tree, each edge has some substring. This prefix of suffix corresponds to this substring
 *     - a range in the suffix array
 *     - a lcp value of this range of suffixes representing length of prefix of these suffixes
 * leaf nodes are a subset of [n - 1, 2 * n - 1), each leaf represents:
 *     - a single suffix
 */
struct lcp_tree {
    int n, root;
    vector<int> sa, sa_inv, lcp, le, ri;
    vector<vector<int>> adj;
    /**
     * @param s non-empty string/array
     * @time O((n log n) + (n * max_val))
     * @space adj is O(n * max_val)
     */
    lcp_tree(const string& s) : n(ssize(s)), adj(max(n - 1, 0), vector(max_val, -1)) {
        assert(n > 0);
        auto ret = get_sa(s, mn + max_val);
        sa = ret[0], sa_inv = ret[1];
        lcp = get_lcp_array(sa, sa_inv, s);
        auto [a_root, a_adj, a_le, a_ri, to_extrema] = get_cart_tree(lcp, less());
        root = max(a_root, 0), le = a_le, ri = a_ri;
        for (int u = 0; u < n - 1; u++)
            for (int v : a_adj[u])
                adj[u][s[sa[v] + lcp[u]] - mn] = v;
        for (int i = 0; i < n; i++) {
            int prev_lcp = (i ? lcp[i - 1] : 0);
            int next_lcp = (i < n - 1 ? lcp[i] : -1);
            int u = (prev_lcp > next_lcp) ? i - 1 : to_extrema[i];
            int idx = sa[i] + max(prev_lcp, next_lcp);
            if (u == -1 || idx == n) continue;
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
    inline array<int, 2> sa_range(int u) {
        if (u < n - 1) return {le[u] + 1, ri[u] + 1};
        return {u - n + 1, u - n + 2};
    }
    /**
     * @param u node
     * @returns length of longest common prefix of u's interval
     * @time O(1)
     * @space O(1)
     */
    inline int lcp_len(int u) {
        return u < n - 1 ? lcp[u] : n - sa[u - n + 1];
    }
    /**
     * @param u node
     * @param c letter (don't subtract mn)
     * @returns child of u following edge with label c, -1 means child doesn't exist
     * @time O(1)
     * @space O(1)
     */
    inline int get_child(int u, char c) {
        return u < n - 1 ? adj[u][c - mn] : -1;
    }
};
