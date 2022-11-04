#pragma once
/**
 * Generic matrix multiplication (not overflow safe). This will RTE if the
 * given matricies are not compatible.
 * @see https://codeforces.com/blog/entry/80195
 * @time O(n * m * inner)
 * @memory O(n * m)
 */
template <typename T> vector<vector<T>> operator * (const vector<vector<T>>& a, const vector<vector<T>>& b) {
	assert(ssize(a[0]) == ssize(b));
	int n = ssize(a), m = ssize(b[0]), inner = ssize(b);
	vector<vector<T>> c(n, vector<T>(m));
	for (int i = 0; i < n; i++)
		for (int k = 0; k < inner; k++)
			for (int j = 0; j < m; j++)
				c[i][j] += a[i][k] * b[k][j];
	return c;
}
