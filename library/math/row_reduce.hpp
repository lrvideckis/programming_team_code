/** @file */
#pragma once
#include "binary_exponentiation_mod.hpp"
/**
 * @code{.cpp}
 *     auto [rank, det] = row_reduce(mat, ssize(mat[0]));
 * @endcode
 * @param mat,cols columns [0,cols) of mat represent a matrix, columns [cols,m)
 * are also affected by row operations.
 * @returns pair(rank, determinant)
 * @time O(n * m * min(cols, n))
 * @memory O(n * m)
 */
pair<int, long long> row_reduce(vector<vector<long long>>& mat, int cols) {
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
			det = det == 0 ? 0 : MOD - det;
			iter_swap(mat.begin() + rank, it);
		}
		det = det * mat[rank][col] % MOD;
		long long a_inv = bin_exp(mat[rank][col], MOD - 2);
		transform(mat[rank].begin(), mat[rank].end(), mat[rank].begin(), [&](auto val) {
			return val * a_inv % MOD;
		});
		for (int i = 0; i < n; i++)
			if (i != rank && mat[i][col] != 0) {
				long long val = mat[i][col];
				transform(mat[i].begin(), mat[i].end(), mat[rank].begin(), mat[i].begin(), [&](auto x, auto y) {
					return (x + (MOD - y) * val) % MOD;
				});
			}
		rank++;
	}
	return {rank, det};
}
