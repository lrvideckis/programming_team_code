#pragma once

#include "exp_mod.h"

struct matrixInfo {
	int rank, det;
};

matrixInfo gauss(vector<vector<int>>& matrix, const int mod) {
	int n = matrix.size();
	int m = matrix[0].size();//possible RTE here
	matrixInfo info{1, 0};
	for(int col = 0, row = 0; col < m && row < n; ++col) {
		int sel = row;
		for(int i = row+1; i < n; ++i)
			if(matrix[i][col] > matrix[sel][col]) sel = i;
		if(matrix[sel][col] == 0) { info.det = 0; continue; }
		for(int j = 0; j < m; ++j) swap(matrix[sel][j], matrix[row][j]);
		if(row != sel) info.det = info.det == 0 ? info.det : mod-info.det;
		info.det = (info.det * matrix[row][col]) % mod;
		int s = fastPow(matrix[row][col], mod-2, mod);
		for(int j = 0; j < m; ++j) matrix[row][j] = (1LL * matrix[row][j] * s) % mod;
		for(int i = 0; i < n; ++i) if (i != row && matrix[i][col] > 0) {
			int t = matrix[i][col];
			for(int j = 0; j < m; ++j) {
				matrix[i][j] -= 1LL * matrix[row][j] * t % mod;
				if(matrix[i][j] < 0) matrix[i][j] += mod;
			}
		}
		++row, ++info.rank;
	}
	return info;
}
