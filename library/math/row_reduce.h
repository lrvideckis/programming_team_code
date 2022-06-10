#pragma once
//library checker tests: https://judge.yosupo.jp/problem/system_of_linear_equations, https://judge.yosupo.jp/problem/matrix_det, https://judge.yosupo.jp/problem/inverse_matrix
//for mod inverse
#include "exp_mod.h"
//First `cols` columns of A represents a matrix to be left in reduced row echelon form
//Row operations will be performed to all later columns
//
//example usage:
//	row_reduce(A, A[0].size(), mod) //row reduce matrix with no extra columns
pair<int/*rank*/, int/*determinant*/> row_reduce(vector<vector<int>>& mat, const int cols, const int mod) {
	int n = mat.size(), m = mat[0].size(), rank = 0, det = 1;
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
		det = (1LL * det * mat[rank][col]) % mod;
		//make pivot 1 by dividing row by inverse of pivot
		const int a_inv = pow(mat[rank][col], mod - 2, mod);
		for (int j = 0; j < m; j++)
			mat[rank][j] = (1LL * mat[rank][j] * a_inv) % mod;
		//zero-out all numbers above & below pivot
		for (int i = 0; i < n; i++)
			if (i != rank && mat[i][col] != 0) {
				const int val = mat[i][col];
				for (int j = 0; j < m; j++) {
					mat[i][j] -= 1LL * mat[rank][j] * val % mod;
					if (mat[i][j] < 0) mat[i][j] += mod;
				}
			}
		rank++;
	}
	assert(rank <= min(n, cols));
	return {rank, det};
}
