#pragma once
#include "monotonic_stack.h"
//stress tests: tests/stress_tests/misc/count_rectangles.cpp
//given a 2D boolean matrix, calculate cnt[i][j]
//cnt[i][j] = the number of times an (i * j) rectangle appears in the matrix such that all i*j cells in the rectangle are true
//Note cnt[0][j] and cnt[i][0] will contain garbage values
//O(n*m)
vector<vector<int>> count_rectangles(const vector<vector<bool>>& grid) {
	const int n = grid.size(), m = grid[0].size();
	vector<vector<int>> cnt(n + 1, vector<int>(m + 1, 0));
	vector<int> arr(m, 0);
	auto rv = [&](int j) -> int {//reverse
		return m - 1 - j;
	};
	for (int i = 0; i < n; i++) {
		vector<pair<int, int>> arr_rev(m);
		for (int j = 0; j < m; j++) {
			arr[j] = grid[i][j] * (arr[j] + 1);
			arr_rev[rv(j)] = {arr[j], j};
		}
		vector<int> left = monotonic_stack(arr);
		vector<int> right = monotonic_stack(arr_rev);
		for (int j = 0; j < m; j++) {
			int L = j - left[j] - 1, R = rv(right[rv(j)]) - j - 1;
			cnt[arr[j]][L + R + 1]++;
			cnt[arr[j]][L]--;
			cnt[arr[j]][R]--;
		}
	}
	for (int i = 1; i <= n; i++)
		for (int k = 0; k < 2; k++)
			for (int j = m; j > 1; j--)
				cnt[i][j - 1] += cnt[i][j];
	for (int j = 1; j <= m; j++)
		for (int i = n; i > 1; i--)
			cnt[i - 1][j] += cnt[i][j];
	return cnt;
}
