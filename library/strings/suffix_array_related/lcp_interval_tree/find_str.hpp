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
    if (lt.root == -1) {
        assert(ssize(lt.sf.sa) <= 1);
        if (t.empty() || lt.s == t) return {0, ssize(lt.s)};
        return {0, 0};
    }
    assert(ssize(lt.sf.sa) >= 2);
    int u = lt.root;
    for (int i = 0; i < ssize(t); i++) {
        if (i == lt.lcp[u]) {
            auto it = lt.child[u].find(t[i]);
            if (it == end(lt.child[u])) return {0, 0};
            u = it->second;
        }
        if (u >= ssize(lt.lcp)) {
            int idx = u - ssize(lt.lcp);
            auto it = mismatch(begin(t) + i, end(t), begin(lt.s) + lt.sf.sa[idx] + i, end(lt.s)).first;
            return {idx, idx + (it == end(t))};
        }
        if (lt.s[lt.sf.sa[u] + i] != t[i]) return {0, 0};
    }
    return {lt.le[u] + 1, lt.ri[u] + 1};
}
