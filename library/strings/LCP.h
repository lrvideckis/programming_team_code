#pragma once
//library checker tests: https://judge.yosupo.jp/problem/zalgorithm, https://judge.yosupo.jp/problem/number_of_substrings, https://judge.yosupo.jp/problem/enumerate_palindromes
//modified from here: https://judge.yosupo.jp/submission/37410
//
// Reference:
// T. Kasai, G. Lee, H. Arimura, S. Arikawa, and K. Park,
// Linear-Time Longest-Common-Prefix Computation in Suffix Arrays and Its
// Applications
template<class T>
vector<int> LCP(const T& s, const vector<int>& sa) {
	int n = s.size(), k = 0;
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
