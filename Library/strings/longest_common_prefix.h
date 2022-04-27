#pragma once

//modified from here: https://judge.yosupo.jp/submission/37410
//
//status: tested on https://judge.yosupo.jp/problem/number_of_substrings (answer = (n * (n+1) / 2) - (sum of LCP array))
//
// Reference:
// T. Kasai, G. Lee, H. Arimura, S. Arikawa, and K. Park,
// Linear-Time Longest-Common-Prefix Computation in Suffix Arrays and Its
// Applications
vector<int> lcp_array(const vector<int>& arr, const vector<int>& sa) {
	int n = arr.size(), k = 0;
	vector<int> lcp(n, 0);
	vector<int> rank(n, 0);
	for (int i = 0; i < n; i++) rank[sa[i]] = i;
	for (int i = 0; i < n; i++, k ? k-- : 0) {
		if (rank[i] == n - 1) {
			k = 0;
			continue;
		}
		int j = sa[rank[i] + 1];
		while (i + k < n && j + k < n && arr[i + k] == arr[j + k]) k++;
		lcp[rank[i]] = k;
	}
	return lcp;
}
