#pragma once
#include "monotonic_stack.h"
//stress tests: tests/stress-tests/misc/cntRectangles.cpp
//given a 2D boolean matrix, calculate cnt[i][j]
//cnt[i][j] = the number of times an (i * j) rectangle appears in the matrix
//such that all cells in the rectangle are true
//Note cnt[0][j] and cnt[i][0] will contain garbage values
//O(R*C)
vector<vector<int>> getNumRectangles(const vector<vector<bool>>& grid) {
	const int n = grid.size(), m = grid[0].size();
	vector<vector<int>> cnt(n + 1, vector<int>(m + 1, 0)), arr(n, vector<int>(m + 1, 0));
	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++) {
			if (grid[i][j])
				arr[i][j] = 1 + (i ? arr[i - 1][j] : 0);
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= m; j++) {
			vector<int> left = monotonic_stack(arr[i]);
			int k = j - 1;
			while (k >= 0 && arr[i][k] > arr[i][j]) {
				int idx = k, len = j - 1 - left[idx];
				k = left[k];
				cnt[arr[i][idx]][len]++;
				cnt[max(arr[i][j], k < 0 ? 0 : arr[i][k])][len]--;
			}
		}
	}
	for (int i = 1; i <= n; i++)
		for (int k = 0; k < 2; k++)
			for (int j = m - 1; j >= 1; j--)
				cnt[i][j] += cnt[i][j + 1];
	for (int j = 1; j <= m; j++)
		for (int i = n - 1; i >= 1; i--)
			cnt[i][j] += cnt[i + 1][j];
	return cnt;
}
