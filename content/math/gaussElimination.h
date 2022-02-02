#pragma once

#include "exp_mod.h"

struct matrixInfo {
	int rank, det;
};

//row reduce matrix to reduced row echelon form
//assumes A is a n by m matrix where n,m >= 1
matrixInfo gauss(vector<vector<int>>& A, const int mod) {
	int n = A.size(), m = A[0].size(), rank = 0, det = 1;
	for(int col = 0; col < m && rank < n; ++col) {
		for(int i = rank; i < n; ++i) if(A[i][col] != 0) {
			if(rank != i) det = det == 0 ? det : mod-det;
			swap(A[i], A[rank]);
			break;
		}
		if(A[rank][col] == 0) { det = 0; continue; }
		det = (1LL * det * A[rank][col]) % mod;
		const int aInv = fastPow(A[rank][col], mod-2, mod);
		for(int j = 0; j < m; ++j) {
			A[rank][j] = (1LL * A[rank][j] * aInv) % mod;
		}
		for(int i = 0; i < n; ++i) if(i != rank && A[i][col] != 0) {
			const int val = A[i][col];
			for(int j = 0; j < m; ++j) {
				A[i][j] -= 1LL * A[rank][j] * val % mod;
				if(A[i][j] < 0) A[i][j] += mod;
			}
		}
		++rank;
	}
	return {rank, det};
}

vector<vector<int>> solve_linear(vector<vector<int>> a, vector<int> b, const int mod) {
	assert(a.size() == b.size());
	int n = a.size(), m = a[0].size();
	for (int i = 0; i < n; ++i) a[i].push_back(b[i]);
	matrixInfo info = gauss(a, mod);
	for (int i = info.rank; i < n; ++i) if (a[i][m] != 0) return {};
	vector<vector<int>> res(1, vector<int>(m));
	vector<int> pivot(m, -1);
	for (int i = 0, j = 0; i < info.rank; ++i) {
		while (a[i][j] == 0) ++j;
		res[0][j] = a[i][m], pivot[j] = i;//TODO: move pivot to row reduce
	}
	for (int j = 0; j < m; ++j) if (pivot[j] == -1) {
		vector<int> x(m);
		x[j] = mod-1;
		for (int k = 0; k < j; ++k) if (pivot[k] != -1) x[k] = a[pivot[k]][j];
		res.push_back(x);
	}
	return res;
}
