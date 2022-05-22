#pragma once

//status: not tested

const int mod = 1e9 + 7;

vector<vector<int>> mult(const vector<vector<int>>& a, const vector<vector<int>>& b) {
	assert(a[0].size() == b.size());
	int resultRow = a.size(), resultCol = b[0].size(), n = a[0].size();
	vector<vector<int>> product(resultRow, vector<int> (resultCol, 0));
	for (int i = 0; i < resultRow; ++i) {
		for (int k = 0; k < n; ++k) {
			for (int j = 0; j < resultCol; ++j)
				product[i][j] = (product[i][j] + 1LL * a[i][k] * b[k][j]) % mod;
		}
	}
	return product;
}

vector<vector<int>> power(vector<vector<int>> matrix, int b) {
	int n = matrix.size();
	vector<vector<int>> res(n, vector<int> (n, 0));
	for (int i = 0; i < n; i++)
		res[i][i] = 1;
	while (b > 0) {
		if (b % 2 == 1)
			res = mult(res, matrix);
		matrix = mult(matrix, matrix);
		b /= 2;
	}
	return res;
}
