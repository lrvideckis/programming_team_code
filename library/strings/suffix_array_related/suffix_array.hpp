/** @file */
#pragma once
/**
 * @see https://github.com/kth-competitive-programming/kactl /blob/main/content/strings/SuffixArray.h
 *
 * @code{.cpp}
 *     string s;
 *     auto [sa, sa_inv] = get_sa(s, 256);
 *     // or
 *     vector<int> arr;
 *     auto [sa, sa_inv] = get_sa(arr, 100'005);
 * @endcode
 *
 * @param s,max_val string/array with 0 <= s[i] < max_val
 * @time O((n log n) + max_val)
 * @space this function allocates O(n) space for `sa`, `sa_inv`
 * vectors, but also allocates a O(max_val) vector `freq` temporarily
 */
template <class T> pair<vector<int>, vector<int>> get_sa(const T& s, int max_val) {
    int n = ssize(s);
    vector<int> sa(n), sa_inv(begin(s), end(s)), tmp(n);
    iota(begin(sa), end(sa), 0);
    for (int len = 0; len < n; len = max(1, 2 * len)) {
        iota(begin(tmp), begin(tmp) + len, n - len);
        copy_if(begin(sa), end(sa), begin(tmp) + len, [&](int& val) {return (val -= len) >= 0;});
        vector<int> freq(max_val);
        for (auto val : sa_inv) freq[val]++;
        partial_sum(begin(freq), end(freq), begin(freq));
        for_each(rbegin(tmp), rend(tmp), [&](int t) {sa[--freq[sa_inv[t]]] = t;});
        swap(sa_inv, tmp);
        max_val = 1, sa_inv[sa[0]] = 0;
        auto prev_inv = [&](int i) {return pair(tmp[i], i + len < n ? tmp[i + len] : -1);};
        for (int i = 1; i < n; i++) {
            max_val += prev_inv(sa[i - 1]) != prev_inv(sa[i]);
            sa_inv[sa[i]] = max_val - 1;
        }
        if (max_val == n) break;
    }
    return {sa, sa_inv};
}
