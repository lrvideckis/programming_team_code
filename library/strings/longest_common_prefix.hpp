#pragma once
//source: https://cp-algorithms.com/string/suffix-array.html
template <typename T> vector<int> calc_lcp(const T& s, const vector<int>& sa) {
	int n = ssize(s);
	vector<int> inv_sa(n), lcp(n - 1, 0);
	for (int i = 0; i < n; i++)
		inv_sa[sa[i]] = i;
	for (int i = 0, k = 0; i < n; i++) {
		if (inv_sa[i] == n - 1) {
			k = 0;
			continue;
		}
		int j = sa[inv_sa[i] + 1];
		while (i + k < n && j + k < n && s[i + k] == s[j + k])
			k++;
		lcp[inv_sa[i]] = k;
		if (k)
			k--;
	}
	return lcp;
}
