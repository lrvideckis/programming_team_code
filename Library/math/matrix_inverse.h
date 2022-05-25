#pragma once
//library checker tests: https://judge.yosupo.jp/problem/inverse_matrix

#include "row_reduce.h"

//returns inverse of square matrix A
vector<vector<int>> matrix_inverse(vector<vector<int>> A/*intentional pass by value*/, const int mod) {
	int n = A.size();
	assert(n == (int)A[0].size());
	//append identity matrix
	for(int i = 0; i < n; i++) {
		A[i].resize(2*n, 0);
		A[i][i+n] = 1;
	}
	auto [rank, det] = row_reduce(A, n, mod);//row reduce first n columns, leaving inverse in last n columns
	if(rank < n) return {}; //no inverse
	for(int i = 0; i < n; i++) {
		A[i].erase(A[i].begin(), A[i].begin() + n);
	}
	return A;
}
