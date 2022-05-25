#pragma once
//library checker tests: https://judge.yosupo.jp/problem/matrix_product

//empty matrix -> RTE

vector<vector<int>> mult(const vector<vector<int>>& a, const vector<vector<int>>& b, int mod) {
	assert(a[0].size() == b.size());
	int n = a.size(), m = b[0].size(), inner = b.size();
	vector<vector<int>> prod(n, vector<int>(m, 0));
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < inner; k++) {
			for (int j = 0; j < m; j++)
				prod[i][j] = (prod[i][j] + 1LL * a[i][k] * b[k][j]) % mod;
		}
	}
	return prod;
}

vector<vector<int>> power(vector<vector<int>> matrix/*intentional pass by value*/, long long pw, int mod) {
	int n = matrix.size();
	vector<vector<int>> prod(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++)
		prod[i][i] = 1;
	while (pw > 0) {
		if (pw % 2 == 1) prod = mult(prod, matrix, mod);
		matrix = mult(matrix, matrix, mod);
		pw /= 2;
	}
	return prod;
}
