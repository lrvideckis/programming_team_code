/** @file */
#pragma once
#include "row_reduce.hpp"
/**
 * Info about matrix and solution vector
 */
struct matrix_info {
	int rank; /**< max number of linearly independent vectors */
	long long det; /**< determinant */
	vector<long long> x; /**< solution vector, empty iff no solution */
};
/**
 * Solves mat * x = b under prime mod. Number of unique solutions = (size of
 * domain) ^ (# of free variables). (# of free variables) is generally
 * equivalent to n - rank.
 *
 * @param mat n (rows) by m (cols) matrix; left in reduced row echelon form
 * @param b length n column vector
 * @returns length m vector x
 * @time O(n * m * min(n, m))
 * @memory O(n * m)
 */
matrix_info solve_linear_mod(vector<vector<long long>>& mat, const vector<long long>& b) {
	assert(ssize(mat) == ssize(b));
	int n = ssize(mat), m = ssize(mat[0]);
	for (int i = 0; i < n; i++)
		mat[i].push_back(b[i]);
	auto [rank, det] = row_reduce(mat, m);
	if (any_of(mat.begin() + rank, mat.end(), [](const auto & v) {return v.back();})) {
		return {rank, det, {}}; //no solution exists
	}
	vector<long long> x(m);
	int j = 0;
	for_each(mat.begin(), mat.begin() + rank, [&](const auto & v) {
		while (v[j] == 0) j++;
		x[j] = v.back();
	});
	return {rank, det, x};
}
