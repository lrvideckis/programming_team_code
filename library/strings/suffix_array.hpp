#pragma once
/**
 * suffixes of "banana":
 * 0 banana
 * 1 anana
 * 2 nana
 * 3 ana
 * 4 na
 * 5 a
 *
 * sorted,  lcp
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
 *
 * suffix array = [5, 3, 1, 0, 4, 2]
 * rank array satisfies sa[rank[i]] == i and rank[sa[i]] == i
 * lcp array = [1, 3, 0, 0, 2, 0] - last 0 is a dummy value
 *
 * @code{.cpp}
 *     string s;
 *     suffix_array info(s, 128);
 *     vector<int> arr;
 *     suffix_array info(arr, 1e5 + 1);
 * @endcode
 * @see https://github.com/kth-competitive-programming/kactl
 * /blob/main/content/strings/SuffixArray.h
 */
template <typename T> struct suffix_array {
	const int N;
	vector<int> sa, rank, lcp;
	/**
	 * Assumes 0 <= s[i] < max_val.
	 * @time O((nlogn) + max_val)
	 * @memory O(n + max_val)
	 */
	suffix_array(const T& s, int max_val) : N(ssize(s)), sa(N), rank(s.begin(), s.end()), lcp(N) {
		iota(sa.begin(), sa.end(), 0);
		vector<int> tmp(N + 1, -1);
		for (int len = 0; len < N; len = max(1, 2 * len)) {//suffix array
			iota(tmp.begin(), tmp.begin() + len, N - len);
			for (int i = 0, j = len; i < N; i++)
				if (sa[i] >= len)
					tmp[j++] = sa[i] - len;
			vector<int> freq(max_val, 0);
			for (int val : rank) freq[val]++;
			partial_sum(freq.begin(), freq.end(), freq.begin());
			for (int i = N - 1; i >= 0; i--)
				sa[--freq[rank[tmp[i]]]] = tmp[i];
			copy(rank.begin(), rank.end(), tmp.begin());
			max_val = 1, rank[sa[0]] = 0;
			for (int i = 1; i < N; i++) {
				int a = sa[i - 1], b = sa[i];
				rank[b] = (tmp[a] == tmp[b] && tmp[a + len] == tmp[b + len]) ? max_val - 1 : max_val++;
			}
			if (max_val == N) break;
		}
		for (int i = 0, k = 0; i < N; i++) {//lcp array
			if (k > 0) k--;
			if (rank[i] == 0) continue;
			int j = sa[rank[i] - 1];
			while (max(i, j) + k < N && s[j + k] == s[i + k]) k++;
			lcp[rank[i] - 1] = k;
		}
	}
};
