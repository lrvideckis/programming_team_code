#pragma once

//source: https://cp-algorithms.com/string/prefix-function.html#implementation
template <class T>
vector<int> prefix_function(const T& s) {
	int n = s.size();
	vector<int> pi(n, 0);
	for (int i = 1; i < n; i++) {
		int j = pi[i - 1];
		while (j > 0 && s[i] != s[j]) j = pi[j - 1];
		pi[i] = j + (s[i] == s[j]);
	}
	return pi;
}
