#pragma once
#include "row_reduce.hpp"
struct matrix_info {
	int rank;
	long long det;
	vector<long long> x;
};
//Solves mat * x = b under prime mod.
//mat is a n (rows) by m (cols) matrix, b is a length n column vector, x is a length m vector.
//assumes n,m >= 1, else RTE
//Returns rank of mat, determinant of mat, and x (solution vector to mat * x = b).
//x is empty if no solution. If rank < m, there are multiple solutions and an arbitrary one is returned.
//Leaves mat in reduced row echelon form (unlike kactl) with b appended.
//Trick: Number of unique solutions = (size of domain) ^ (# of free variables).
//# of free variables is generally equivalent to n - rank.
//O(n * m * min(n,m))
matrix_info solve_linear_mod(vector<vector<long long>>& mat, const vector<long long>& b, long long mod) {
	assert(ssize(mat) == ssize(b));
	int n = ssize(mat), m = ssize(mat[0]);
	for (int i = 0; i < n; i++)
		mat[i].push_back(b[i]);
	auto [rank, det] = row_reduce(mat, m, mod);//row reduce not including the last column
	//check if solution exists
	for (int i = rank; i < n; i++) {
		if (mat[i].back() != 0) return {rank, det, {} }; //no solution exists
	}
	//initialize solution vector (`x`) from row-reduced matrix
	vector<long long> x(m, 0);
	for (int i = 0, j = 0; i < rank; i++) {
		while (mat[i][j] == 0) j++; //find pivot column
		x[j] = mat[i].back();
	}
	return {rank, det, x};
}
