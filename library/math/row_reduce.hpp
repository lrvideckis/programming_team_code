/** @file */
#pragma once
#include "binary_exponentiation_mod.hpp"
/**
 * @code{.cpp}
 *     auto [rank, det] = row_reduce(mat, ssize(mat[0]), mod);
 * @endcode
 * @param mat,cols columns [0,cols) of mat represent a matrix, columns [cols,m)
 * are also affected by row operations.
 * @param mod a prime
 * @returns pair(rank, determinant)
 * @time O(n * m * min(cols, n))
 * @memory O(n * m)
 */
pair<int, long long> row_reduce(vector<vector<long long>>& mat, int cols, long long mod) {
	int n = ssize(mat), m = ssize(mat[0]), rank = 0;
	long long det = 1;
	assert(cols <= m);
	for (int col = 0; col < cols && rank < n; col++) {
		auto it = find_if(mat.begin() + rank, mat.end(), [&](const auto & v) {return v[col];});
		if (it == mat.end()) {
			det = 0;
			continue;
		}
		if (it != mat.begin() + rank) {
			det = det == 0 ? 0 : mod - det;
			iter_swap(mat.begin() + rank, it);
		}
		det = det * mat[rank][col] % mod;
		long long a_inv = bin_exp(mat[rank][col], mod - 2, mod);
		transform(mat[rank].begin(), mat[rank].end(), mat[rank].begin(), [&](auto val) {
			return val * a_inv % mod;
		});
		for (int i = 0; i < n; i++)
			if (i != rank && mat[i][col] != 0) {
				long long val = mat[i][col];
				transform(mat[i].begin(), mat[i].end(), mat[rank].begin(), mat[i].begin(), [&](auto x, auto y) {
					return (x + (mod - y) * val) % mod;
				});
			}
		rank++;
	}
	assert(rank <= min(n, cols));
	return {rank, det};
}
