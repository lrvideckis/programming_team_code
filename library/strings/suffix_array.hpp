/** @file */
#pragma once
/**
 * suffixes of "banana":
 * 0 banana
 * 1 anana
 * 2 nana
 * 3 ana
 * 4 na
 * 5 a
 * sorted,  longest common prefix (lcp)
 * 5 a
 *   |      1
 * 3 ana
 *   |||    3
 * 1 anana
 *          0
 * 0 banana
 *          0
 * 4 na
 *   ||     2
 * 2 nana
 * sa = [5, 3, 1, 0, 4, 2]
 * rank = [3, 2, 5, 1, 4, 0] (sa[rank[i]] == i, rank[sa[i]] == i)
 * lcp = [1, 3, 0, 0, 2]
 */
struct sa_info {
    vector<int> sa, rank, lcp;
};
/**
 * @see https://github.com/kth-competitive-programming/kactl /blob/main/content/strings/SuffixArray.h
 *
 * @code{.cpp}
 *     string s;
 *     auto [sa, rank, lcp] = get_suffix_array(s, 128);
 *     vector<int> arr;
 *     auto [sa, rank, lcp] = get_suffix_array(arr, 100'005);
 * @endcode
 */
template <typename T> sa_info get_suffix_array(const T& s, int max_val) {
    int n = ssize(s);
    vector<int> sa(n), rank(n), tmp(n);
    iota(begin(sa), end(sa), 0);
    for (int len = 0; len < n; len = max(1, 2 * len)) {
        iota(begin(tmp), begin(tmp) + len, n - len);
        copy_if(begin(sa), end(sa), begin(tmp) + len, [&](int& val) {return (val -= len) >= 0;});
        vector<int> freq(max_val);
        for (auto val : rank) freq[val]++;
        partial_sum(begin(freq), end(freq), begin(freq));
        for_each(rbegin(tmp), rend(tmp), [&](int t) {sa[--freq[rank[t]]] = t;});
        swap(rank, tmp);
        max_val = 1, rank[sa[0]] = 0;
        auto prev_rank = [&](int i) {return pair(tmp[i], i + len < n ? tmp[i + len] : -1);};
        for (int i = 1; i < n; i++) {
            max_val += prev_rank(sa[i - 1]) != prev_rank(sa[i]);
            rank[sa[i]] = max_val - 1;
        }
        if (max_val == n) break;
    }
    vector<int> lcp(max(0, n - 1));
    for (int i = 0, k = 0; i < n; i++) {
        if (k > 0) k--;
        if (rank[i] == 0) continue;
        for (int j = sa[rank[i] - 1]; max(i, j) + k < n && s[i + k] == s[j + k];) k++;
        lcp[rank[i] - 1] = k;
    }
    return {sa, rank, lcp};
}
