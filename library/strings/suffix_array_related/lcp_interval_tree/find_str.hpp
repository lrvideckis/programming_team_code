/** @file */
#pragma once
#include "lcp_interval_tree.hpp"
/**
 * performs trie-style downwards tree walk
 *
 * @param lt lcp interval tree
 * @param t needle
 * @returns range [le, ri) such that:
 * - for all i in [le, ri): t == s.substr(sf.sa[i], ssize(t))
 * - `ri - le` is the # of matches of t in s.
 * @time O(|t| * log(|alphabet|)); |alphabet| = 26 if only lowercase letters
 * @space O(1)
 */
template <class T> pair<int, int> find_str(const lcp_tree<T>& lt, const T& t) {
    int u = max(lt.root, 0);
    for (int i = 0; i < ssize(t); i++) {
        if (i == lt.lcp_len(u)) {
            if (u >= ssize(lt.child)) return {0, 0};
            auto it = lt.child[u].find(t[i]);
            if (it == end(lt.child[u])) return {0, 0};
            u = it->second;
        }
        auto [le, ri] = lt.sa_range(u);
        if (lt.s[lt.sf.sa[le] + i] != t[i]) return {0, 0};
    }
    return lt.sa_range(u);
}
