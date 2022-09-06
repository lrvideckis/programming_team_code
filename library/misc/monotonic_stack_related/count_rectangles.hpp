#pragma once
#include "monotonic_stack.hpp"
//given a 2D boolean matrix, calculate cnt[i][j]
//cnt[i][j] = the number of times an i-by-j rectangle appears in the matrix such that all i*j cells in the rectangle are 1
//Note cnt[0][j] and cnt[i][0] will contain garbage values
//O(n*m)
vector<vector<int>> count_rectangles(const vector<vector<bool>>& grid) {
	int n = grid.size(), m = grid[0].size();
	vector<vector<int>> cnt(n + 1, vector<int>(m + 1, 0));
	vector<int> arr(m, 0);
	auto rv /*reverse*/ = [&](int j) -> int {
		return m - 1 - j;
	};
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			arr[j] = grid[i][j] * (arr[j] + 1);
		vector<int> left = monotonic_stack<int>(arr, greater());
		vector<int> right = monotonic_stack<int>(vector<int>(arr.rbegin(), arr.rend()), greater_equal());
		for (int j = 0; j < m; j++) {
			int l = j - left[j] - 1, r = rv(right[rv(j)]) - j - 1;
			cnt[arr[j]][l + r + 1]++;
			cnt[arr[j]][l]--;
			cnt[arr[j]][r]--;
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
