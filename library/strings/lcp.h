#pragma once
//source: https://judge.yosupo.jp/submission/37410
//mnemonic: Longest Common Prefix
//NOLINTNEXTLINE(readability-identifier-naming)
template<class T> vector<int> LCP(const T& s, const vector<int>& sa) {
	int n = ssize(s), k = 0;
	vector<int> lcp(n, 0);
	vector<int> rank(n, 0);
	for (int i = 0; i < n; i++) rank[sa[i]] = i;
	for (int i = 0; i < n; i++, k ? k-- : 0) {
		if (rank[i] == n - 1) {
			k = 0;
			continue;
		}
		int j = sa[rank[i] + 1];
		while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
		lcp[rank[i]] = k;
	}
	return lcp;
}
