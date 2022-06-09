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
	vector<vector<int>> cnt(n + 1, vector<int>(m + 1, 0));
	vector<int> arr(m, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			arr[j] = grid[i][j] * (arr[j] + 1);
		vector<int> left = monotonic_stack(arr);
		vector<pair<int, int>> arrRev(m);
		for (int j = 0; j < m; j++)
			arrRev[m - 1 - j] = {arr[j], j};
		vector<int> right = monotonic_stack(arrRev);
		for (int j = 0; j < m; j++) {
			int rig = (m - 1 - right[m - 1 - j]) - j, lef = j - left[j] - 1;
			cnt[arr[j]][rig + lef]++;
			cnt[arr[j]][lef]--;
			cnt[arr[j]][rig - 1]--;
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
