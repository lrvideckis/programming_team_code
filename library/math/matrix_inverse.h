#pragma once
//library checker tests: https://judge.yosupo.jp/problem/inverse_matrix
#include "row_reduce.h"
//returns inverse of square matrix mat, empty if no inverse
vector<vector<int>> matrix_inverse(vector<vector<int>> mat/*intentional pass by value*/, const int mod) {
	int n = mat.size();
	assert(n == (int)mat[0].size());
	//append identity matrix
	for (int i = 0; i < n; i++) {
		mat[i].resize(2 * n, 0);
		mat[i][i + n] = 1;
	}
	auto [rank, det] = row_reduce(mat, n, mod);//row reduce first n columns, leaving inverse in last n columns
	if (rank < n) return {}; //no inverse
	for (int i = 0; i < n; i++)
		mat[i].erase(mat[i].begin(), mat[i].begin() + n);
	return mat;
}
