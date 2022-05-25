#pragma once
//library checker tests: https://judge.yosupo.jp/problem/system_of_linear_equations, https://judge.yosupo.jp/problem/matrix_det

//for mod inverse
#include "exp_mod.h"

struct matrixInfo {
	int rank, det;
	vector<int> x;
};

//Solves A * x = b under prime mod.
//A is a n (rows) by m (cols) matrix, b is a length n column vector, x is a length m column vector.
//assumes n,m >= 1, else RTE
//Returns rank of A, determinant of A, and x (solution vector to A * x = b). x is empty if no solution. If multiple solutions, an arbitrary one is returned.
//Leaves A in reduced row echelon form (unlike kactl).
//O(n * m * min(n,m))
matrixInfo solve_linear_mod(vector<vector<int>>& A, vector<int>& b, const int mod) {
	assert(A.size() == b.size());
	int n = A.size(), m = A[0].size(), rank = 0, det = 1;
	//start of row reduce
	for (int col = 0; col < m && rank < n; col++) {
		//find arbitrary pivot and swap pivot to current row
		for (int i = rank; i < n; i++)
			if (A[i][col] != 0) {
				if (rank != i) det = det == 0 ? det : mod - det;
				swap(A[i], A[rank]);
				swap(b[i], b[rank]);
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
		b[rank] = (1LL * b[rank] * aInv) % mod;
		//zero-out all numbers above & below pivot
		for (int i = 0; i < n; i++)
			if (i != rank && A[i][col] != 0) {
				const int val = A[i][col];
				for (int j = 0; j < m; j++) {
					A[i][j] -= 1LL * A[rank][j] * val % mod;
					if (A[i][j] < 0) A[i][j] += mod;
				}
				b[i] -= 1LL * b[rank] * val % mod;
				if (b[i] < 0) b[i] += mod;
			}
		rank++;
	}
	//end of row reduce, start of extracting answer (`x`) from `A` and `b`
	assert(rank <= min(n, m));
	//check if solution exists
	for (int i = rank; i < n; i++) {
		if (b[i] != 0) return {rank, det, {} }; //no solution exists
	}
	//initialize solution vector (`x`)
	vector<int> x(m, 0);
	for (int i = 0, j = 0; i < rank; i++) {
		while (A[i][j] == 0) j++; //find pivot column
		assert(A[i][j] == 1);
		x[j] = b[i];
	}
	return {rank, det, x};
}
