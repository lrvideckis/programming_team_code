#pragma once
//library checker tests: https://judge.yosupo.jp/problem/system_of_linear_equations, https://judge.yosupo.jp/problem/matrix_det, https://judge.yosupo.jp/problem/inverse_matrix

//for mod inverse
#include "exp_mod.h"

//First `cols` columns of A represents a matrix to be left in reduced row echelon form
//Row operations will be performed to all later columns
//
//example usage:
//	row_reduce(A, A[0].size(), mod) //row reduce matrix with no extra columns
pair<int/*rank*/, int/*determinant*/> row_reduce(vector<vector<int>>& A, const int cols, const int mod) {
	int n = A.size(), m = A[0].size(), rank = 0, det = 1;
	assert(cols <= m);
	for (int col = 0; col < cols && rank < n; col++) {
		//find arbitrary pivot and swap pivot to current row
		for (int i = rank; i < n; i++)
			if (A[i][col] != 0) {
				if (rank != i) det = det == 0 ? 0 : mod - det;
				swap(A[i], A[rank]);
				break;
			}
		if (A[rank][col] == 0) {
			det = 0;
			continue;
		}
		det = (1LL * det * A[rank][col]) % mod;
		//make pivot 1 by dividing row by inverse of pivot
		const int aInv = fastPow(A[rank][col], mod - 2, mod);
		for (int j = 0; j < m; j++)
			A[rank][j] = (1LL * A[rank][j] * aInv) % mod;
		//zero-out all numbers above & below pivot
		for (int i = 0; i < n; i++)
			if (i != rank && A[i][col] != 0) {
				const int val = A[i][col];
				for (int j = 0; j < m; j++) {
					A[i][j] -= 1LL * A[rank][j] * val % mod;
					if (A[i][j] < 0) A[i][j] += mod;
				}
			}
		rank++;
	}
	assert(rank <= min(n, cols));
	return {rank, det};
}
