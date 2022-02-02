#pragma once

#include "exp_mod.h"

struct matrixInfo {
	int rank, det;
	vector<int> sol;
};

//row reduce matrix to reduced row echelon form
//assumes A is a n by m matrix where n,m >= 1
matrixInfo solve_linear(vector<vector<int>>& A, vector<int>& b, const int mod) {
	assert(A.size() == b.size());
	int n = A.size(), m = A[0].size(), rank = 0, det = 1;
	vector<int> pivot;
	for(int col = 0; col < m && rank < n; ++col) {
		for(int i = rank; i < n; ++i) if(A[i][col] != 0) {
			if(rank != i) det = det == 0 ? det : mod-det;
			swap(A[i], A[rank]);
			swap(b[i], b[rank]);
			break;
		}
		if(A[rank][col] == 0) { det = 0; continue; }
		det = (1LL * det * A[rank][col]) % mod;
		pivot.push_back(col);
		{
			int aInv = fastPow(A[rank][col], mod-2, mod);
			for(int j = 0; j < m; ++j) {
				A[rank][j] = (1LL * A[rank][j] * aInv) % mod;
			}
			b[rank] = (1LL * b[rank] * aInv) % mod;
		}
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
	assert(rank == (int)pivot.size());

	matrixInfo info{rank, det, vector<int>()};
	for(int i = rank; i < n; i++) {
		if(b[i] != 0) return info;
	}
	info.sol.resize(m, 0);
	for(int i = 0; i < rank; i++) {
		assert(A[i][pivot[i]] == 1 && (pivot[i] == 0 || A[i][pivot[i]-1] == 0));
		info.sol[pivot[i]] = b[i];
	}

	return info;
}
