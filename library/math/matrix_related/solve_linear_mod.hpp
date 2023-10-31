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
 * equivalent to m - rank.
 *
 * @param mat n (rows) by m (cols) matrix; left in reduced row echelon form
 * @param b length n column vector
 * @returns length m vector x
 * @time O(n * m * min(n, m))
 * @space besides the O(n * m) `mat` param, this function allocates/returns a
 * O(m) solution vector
 */
matrix_info solve_linear_mod(vector<vector<long long>>& mat, const vector<long long>& b) {
    assert(ssize(mat) == ssize(b));
    auto n = ssize(mat), m = ssize(mat[0]);
    for (auto i = 0; i < n; i++)
        mat[i].push_back(b[i]);
    auto [rank, det] = row_reduce(mat, int(m));
    if (any_of(begin(mat) + rank, end(mat), [](auto& v) {return v.back();})) {
        return {rank, det, {}}; //no solution exists
    }
    vector x(m, 0LL);
    int j = 0;
    for_each(begin(mat), begin(mat) + rank, [&](auto& v) {
        while (v[j] == 0) j++;
        x[j] = v.back();
    });
    return {rank, det, x};
}
