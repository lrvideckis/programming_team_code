#pragma once
template <typename T> struct suffix_array {
	const int N;
	vector<int> sa, rank;
	suffix_array(const T& s, int max_val) : N(ssize(s)), sa(N), rank(s.begin(), s.end()) {
		iota(sa.begin(), sa.end(), 0);
		vector<int> tmp(N + 1, -1);
		for (int len = 0; len < N; len = max(1, 2 * len)) {
			iota(tmp.begin(), tmp.begin() + len, N - len);
			for (int i = 0, p = len; i < N; i++)
				if (sa[i] >= len)
					tmp[p++] = sa[i] - len;
			vector<int> freq(max_val, 0);
			for (int val : rank)
				freq[val]++;
			partial_sum(freq.begin(), freq.end(), freq.begin());
			for (int i = N - 1; i >= 0; i--)
				sa[--freq[rank[tmp[i]]]] = tmp[i];
			copy(rank.begin(), rank.end(), tmp.begin());
			max_val = 1, rank[sa[0]] = 0;
			for (int i = 1; i < N; i++) {
				int a = sa[i - 1], b = sa[i];
				rank[b] = (tmp[a] == tmp[b] && tmp[a + len] == tmp[b + len]) ? max_val - 1 : max_val++;
			}
			if (max_val == N)
				break;
		}
	}
};
