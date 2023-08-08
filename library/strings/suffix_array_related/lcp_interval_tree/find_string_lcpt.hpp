/** @file */
#pragma once
#include "lcp_interval_tree.hpp"
/**
 * performs trie-style downwards tree walk
 *
 * @code{.cpp}
 *     string s, t;
 *     lcp_tree lt(s, 256);
 *     auto [le, ri] = find_str(lt, t);
 * @endcode
 *
 * @param lt lcp interval tree
 * @param t needle
 * @returns range [le, ri) such that:
 *     - for all i in [le, ri): t == s.substr(sf.sa[i], ssize(t))
 *     - `ri - le` is the # of matches of t in s.
 * @time O(|t|)
 * @space O(1)
 */
pair<int, int> find_str(const lcp_tree& lt, const string& t) {
    int u = max(lt.root, 0);
    for (int i = 0; i < ssize(t); i++) {
        if (i == lt.lcp_len(u)) {
            u = lt.get_child(u, t[i]);
            if (u == -1) return {0, 0};
        }
        auto [le, ri] = lt.sa_range(u);
        if (lt.s[lt.sa[le] + i] != t[i]) return {0, 0};
    }
    return lt.sa_range(u);
}
