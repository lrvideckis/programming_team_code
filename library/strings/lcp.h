#pragma once
//source: https://judge.yosupo.jp/submission/37410
//mnemonic: Longest Common Prefix
//NOLINTNEXTLINE(readability-identifier-naming)
template<class T> vector<int> LCP(const T& s, const vector<int>& sa, const vector<int>& sa_inv) {
	int n = s.size();
	vector<int> lcp(n, 0);
	for (int i = 0, k = 0; i < n; i++, k ? k-- : 0) {
		if (sa_inv[i] == n - 1) {
			k = 0;
			continue;
		}
		int j = sa[sa_inv[i] + 1];
		while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
		lcp[sa_inv[i]] = k;
	}
	return lcp;
}
