#pragma once

const int mod = 1e9 + 7;

vector<vector<int>> mult(const vector<vector<int>> &a, const vector<vector<int>> &b) {
	if(a.size() == 0) return {};
	if(a[0].size() == 0) return {};
	if(b.size() == 0) return {};
	if(b[0].size() == 0) return {};
	if(a[0].size() != b.size()) return {};
	int resultRow = a.size(), resultCol = b[0].size(), n = a[0].size();
	vector<vector<int>> product(resultRow, vector<int>(resultCol,0));
	for(int i = 0; i < resultRow; ++i) {
		for(int k = 0; k < n; ++k) {
			for(int j = 0; j < resultCol; ++j) {
				product[i][j] = (product[i][j] + 1LL * a[i][k] * b[k][j]) % mod;
			}
		}
	}
	return product;
}

vector<vector<int>> power(vector<vector<int>> matrix, int b) {
	vector<vector<int>> res(matrix.size(),vector<int>(matrix.size(),0));
	for(int i = 0; i < (int)matrix.size(); i++) {
		res[i][i] = 1;
	}
	while(b > 0) {
		if(b%2 == 1) {
			res = mult(res,matrix);
		}
		matrix = mult(matrix, matrix);
		b /= 2;
	}
	return res;
}
