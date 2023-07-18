/** @file */
#pragma once
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
 *     auto lcp = get_lcp_array(s, sa, sa_inv);
 *     vector<int> arr;
 *     auto [sa, sa_inv] = get_sa(arr, 100'005);
 *     auto lcp = get_lcp_array(arr, sa, sa_inv);
 * @endcode
 *
 * @param s,sa,sa_inv string/array and its suffix array
 * @returns lcp vector
 * @time O(n)
 * @space this function allocates O(n) space for `lcp`
 */
template <typename T> vector<int> get_lcp_array(const T& s, const vector<int>& sa, const vector<int>& sa_inv) {
    int n = ssize(s);
    vector<int> lcp(max(0, n - 1));
    for (int i = 0, sz = 0; i < n; i++) {
        if (sz > 0) sz--;
        if (sa_inv[i] == 0) continue;
        for (int j = sa[sa_inv[i] - 1]; max(i, j) + sz < n && s[i + sz] == s[j + sz];) sz++;
        lcp[sa_inv[i] - 1] = sz;
    }
    return lcp;
}
