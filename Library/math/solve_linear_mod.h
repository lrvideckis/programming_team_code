#pragma once
//library checker tests: https://judge.yosupo.jp/problem/system_of_linear_equations

#include "row_reduce.h"

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
matrixInfo solve_linear_mod(vector<vector<int>>& A, const vector<int>& b, const int mod) {
	assert(A.size() == b.size());
	int n = A.size(), m = A[0].size();
	for(int i = 0; i < n; i++)
		A[i].push_back(b[i]);
	auto [rank, det] = row_reduce(A, m, mod);//row reduce not including the last column
	//check if solution exists
	for (int i = rank; i < n; i++) {
		if (A[i].back() != 0) return {rank, det, {} }; //no solution exists
	}
	//initialize solution vector (`x`) from row-reduced matrix
	vector<int> x(m, 0);
	for (int i = 0, j = 0; i < rank; i++) {
		while (A[i][j] == 0) j++; //find pivot column
		assert(A[i][j] == 1);
		x[j] = A[i].back();
	}
	for(int i = 0; i < n; i++)
		A[i].pop_back();//optional
	return {rank, det, x};
}
