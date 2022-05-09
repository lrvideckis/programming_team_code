#pragma once

//status: not tested
//
//**for directed graphs only** if you initialize len[i][i] to infinity, then
//afterward floyds, len[i][i] = length of shortest cycle including node `i`
//
//another trick: change `len` to 2d array of *bools* where len[i][j] = true if
//there exists an edge from i -> j in initial graph. Also do:
//`len[i][j] |= len[i][k] & len[k][j]`
//Then after floyds, len[i][j] = true iff there's exists some path from node
//`i` to node `j`
//
//Changing the order of for-loops to i-j-k (instead of the current k-i-j)
//results in min-plus matrix multiplication. If adjacency matrix is M, then
//after computing M^k (with binary exponentiation), M[i][j] = min length path
//from i to j with at most k edges.

for (int k = 0; k < n; k++)
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			len[i][j] = min(len[i][j], len[i][k] + len[k][j]);
