/** @file */
#pragma once
#include "suffix_array.hpp"
/**
 * @see https://github.com/kth-competitive-programming/kactl /blob/main/content/strings/SuffixArray.h
 *
 * suffixes of "banana", sorted:
 * a
 * |      1
 * ana
 * |||    3
 * anana
 *        0
 * banana
 *        0
 * na
 * ||     2
 * nana
 *
 * lcp = {1, 3, 0, 0, 2}
 *
 * @code{.cpp}
 *     string s;
 *     auto [sa, sa_inv] = get_sa(s, 256);
 *     vector<int> lcp = get_lcp_array({sa, sa_inv}, s);
 *     // or
 *     vector<int> arr;
 *     auto [sa, sa_inv] = get_sa(arr, 100'005);
 *     vector<int> lcp = get_lcp_array({sa, sa_inv}, arr);
 * @endcode
 *
 * @param sf,s string/array and its suffix array
 * @returns lcp vector
 * @time O(n)
 * @space this function allocates O(n) space for `lcp`
 */
template <class T> vector<int> get_lcp_array(const suf& sf, const T& s) {
    int n = ssize(s);
    vector<int> lcp(max(0, n - 1));
    for (int i = 0, sz = 0; i < n; i++) {
        if (sz > 0) sz--;
        if (sf.sa_inv[i] == 0) continue;
        for (int j = sf.sa[sf.sa_inv[i] - 1]; max(i, j) + sz < n && s[i + sz] == s[j + sz];) sz++;
        lcp[sf.sa_inv[i] - 1] = sz;
    }
    return lcp;
}
