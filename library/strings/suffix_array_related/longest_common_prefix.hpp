/** @file */
#pragma once
/**
 * @see https://github.com/kth-competitive-programming/kactl /blob/main/content/strings/SuffixArray.h
 *
 * suffixes of "banana":
 * 0 banana 3
 * 1 anana  2
 * 2 nana   5
 * 3 ana    1
 * 4 na     4
 * 5 a      0
 * sorted,     longest common prefix (lcp)
 * 5 a      0
 *   |         1
 * 3 ana    1
 *   |||       3
 * 1 anana  2
 *             0
 * 0 banana 3
 *             0
 * 4 na     4
 *   ||        2
 * 2 nana   5
 *
 * sa = [5, 3, 1, 0, 4, 2]
 * sa_inv = [3, 2, 5, 1, 4, 0] (sa[sa_inv[i]] == i, sa_inv[sa[i]] == i)
 * lcp = [1, 3, 0, 0, 2]
 *
 * @code{.cpp}
 *     string s;
 *     auto [sa, sa_inv] = get_sa(s, 256);
 *     auto lcp = get_lcp(s, sa, sa_inv);
 * @endcode
 *
 * @param s,max_val string/array with 0 <= s[i] < max_val
 * @returns suffix array and lcp vectors
 * @time O(n)
 * @space this function allocates O(n) space for `lcp`
 */
template <typename T> vector<int> get_lcp(const T& s, const vector<int>& sa, const vector<int>& sa_inv) {
    int n = ssize(s);
    vector<int> lcp(max(0, n - 1));
    for (int i = 0, k = 0; i < n; i++) {
        if (k > 0) k--;
        if (sa_inv[i] == 0) continue;
        for (int j = sa[sa_inv[i] - 1]; max(i, j) + k < n && s[i + k] == s[j + k];) k++;
        lcp[sa_inv[i] - 1] = k;
    }
    return lcp;
}
