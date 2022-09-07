#pragma once

// generic matrix multiplication (not overflow safe)
// will RTE if the given matricies are not compatible
// Time: O(n * m * inner)
// Space: O(n * m)

template<typename T> vector<vector<T>> operator * (const vector<vector<T>>& a, const vector<vector<T>>& b) {
	assert(a[0].size() == b.size());
	int n = a.size(), m = b[0].size(), inner = b.size();
	vector<vector<T>> c(n, vector<T>(m));
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < inner; k++) {
			for (int j = 0; j < m; j++)
				c[i][j] = c[i][j] + a[i][k] * b[k][j];
		}
	}
	return c;
}