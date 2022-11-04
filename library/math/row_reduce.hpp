#pragma once
//for mod inverse
#include "binary_exponentiation_mod.hpp"
//First `cols` columns of mat represents a matrix to be left in reduced row echelon form
//Row operations will be performed to all later columns
//
//example usage:
//	auto [rank, det] = row_reduce(mat, ssize(mat[0]), mod) //row reduce matrix with no extra columns
pair<int/*rank*/, long long/*determinant*/> row_reduce(vector<vector<long long>>& mat, int cols, long long mod) {
	int n = ssize(mat), m = ssize(mat[0]), rank = 0;
	long long det = 1;
	assert(cols <= m);
	for (int col = 0; col < cols && rank < n; col++) {
		//find arbitrary pivot and swap pivot to current row
		for (int i = rank; i < n; i++)
			if (mat[i][col] != 0) {
				if (rank != i) det = det == 0 ? 0 : mod - det;
				swap(mat[i], mat[rank]);
				break;
			}
		if (mat[rank][col] == 0) {
			det = 0;
			continue;
		}
		det = det * mat[rank][col] % mod;
		//make pivot 1 by dividing row by inverse of pivot
		long long a_inv = bin_exp(mat[rank][col], mod - 2, mod);
		for (int j = 0; j < m; j++)
			mat[rank][j] = mat[rank][j] * a_inv % mod;
		//zero-out all numbers above & below pivot
		for (int i = 0; i < n; i++)
			if (i != rank && mat[i][col] != 0) {
				long long val = mat[i][col];
				for (int j = 0; j < m; j++) {
					mat[i][j] -= mat[rank][j] * val % mod;
					if (mat[i][j] < 0) mat[i][j] += mod;
				}
			}
		rank++;
	}
	assert(rank <= min(n, cols));
	return {rank, det};
}
