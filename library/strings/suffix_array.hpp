/** @file */
#pragma once
/**
 * @see https://github.com/kth-competitive-programming/kactl
 * /blob/main/content/strings/SuffixArray.h
 *
 * @code{.cpp}
 *     string s;
 *     suffix_array info(s, 128);
 *     vector<int> arr;
 *     suffix_array info(arr, 100'005);
 * @endcode
 */
template <typename T> struct suffix_array {
    const int N;
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
     * @{
     */
    vector<int> sa, rank, lcp;
    /** @} */
    /**
     * @param s,max_val string/array with 0 <= s[i] < max_val
     * @time O((n log n) + max_val)
     * @space this function allocates O(n) space for `sa`, `rank`, and `lcp`
     * vectors, but also allocates a O(max_val) vector `freq` temporarily
     */
    suffix_array(const T& s, int max_val) : N(ssize(s)), sa(N), rank(begin(s), end(s)), lcp(max(0, N - 1)) {
        iota(begin(sa), end(sa), 0);
        vector<int> tmp(N);
        for (int len = 0; len < N; len = max(1, 2 * len)) {
            iota(begin(tmp), begin(tmp) + len, N - len);
            copy_if(begin(sa), end(sa), begin(tmp) + len, [&](int& val) {return (val -= len) >= 0;});
            vector<int> freq(max_val);
            for (auto val : rank) freq[val]++;
            partial_sum(begin(freq), end(freq), begin(freq));
            for_each(rbegin(tmp), rend(tmp), [&](int t) {
                sa[--freq[rank[t]]] = t;
            });
            swap(rank, tmp);
            max_val = 1, rank[sa[0]] = 0;
            auto prev_rank = [&](int i) {return pair(tmp[i], i + len < N ? tmp[i + len] : -1);};
            for (int i = 1; i < N; i++) {
                max_val += prev_rank(sa[i - 1]) != prev_rank(sa[i]);
                rank[sa[i]] = max_val - 1;
            }
            if (max_val == N) break;
        }
        for (int i = 0, k = 0; i < N; i++) {
            if (k > 0) k--;
            if (rank[i] == 0) continue;
            for (int j = sa[rank[i] - 1]; max(i, j) + k < N && s[i + k] == s[j + k];) k++;
            lcp[rank[i] - 1] = k;
        }
    }
};
