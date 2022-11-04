#pragma once
template <typename T> struct suffix_array {
	const int N;
	vector<int> sa, rank, lcp;
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
