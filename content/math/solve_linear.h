#pragma once

#include "exp_mod.h"

struct matrixInfo {
	int rank, det;
	vector<int> x;
};

//Solves A * x = b under prime mod.
//A is a n (rows) by m (cols) matrix, b is a length n column vector, x is a length m column vector.
//assumes n,m >= 1, else RTE
//Returns rank of A, determinant of A, and x (solution vector). x is empty if no solution. If multiple solutions, an arbitrary one is returned.
//Leaves A in reduced row echelon form (unlike kactl).
//O(n * m * min(n,m))
//
//status: tested on https://judge.yosupo.jp/problem/system_of_linear_equations and https://judge.yosupo.jp/problem/matrix_det
matrixInfo solve_linear(vector<vector<int>>& A, vector<int>& b, const int mod) {
	assert(A.size() == b.size());
	int n = A.size(), m = A[0].size(), rank = 0, det = 1;
	for(int col = 0; col < m && rank < n; ++col) {
		for(int i = rank; i < n; ++i) if(A[i][col] != 0) {
			if(rank != i) det = det == 0 ? det : mod-det;
			swap(A[i], A[rank]);
			swap(b[i], b[rank]);
			break;
		}
		if(A[rank][col] == 0) { det = 0; continue; }
		det = (1LL * det * A[rank][col]) % mod;
		const int aInv = fastPow(A[rank][col], mod-2, mod);
		for(int j = 0; j < m; ++j) {
			A[rank][j] = (1LL * A[rank][j] * aInv) % mod;
		}
		b[rank] = (1LL * b[rank] * aInv) % mod;
		for(int i = 0; i < n; ++i) if(i != rank && A[i][col] != 0) {
			const int val = A[i][col];
			for(int j = 0; j < m; ++j) {
				A[i][j] -= 1LL * A[rank][j] * val % mod;
				if(A[i][j] < 0) A[i][j] += mod;
			}
			b[i] -= 1LL * b[rank] * val % mod;
			if(b[i] < 0) b[i] += mod;
		}
		++rank;
	}
	assert(rank <= min(n,m));

	matrixInfo info{rank, det, vector<int>()};
	for(int i = rank; i < n; i++) {
		if(b[i] != 0) return info;//no solution exists
	}
	info.x.resize(m, 0);
	for(int i = 0, j = 0; i < rank; i++) {
		while(A[i][j] == 0) j++;
		assert(A[i][j] == 1);
		info.x[j] = b[i];
	}

	return info;
}
