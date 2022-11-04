#pragma once
#include "monotonic_stack.hpp"
/**
 * Given a n-by-m boolean matrix, calculate cnt[i][j]. cnt[i][j] = the number
 * of times an i-by-j sub rectangle appears in the matrix such that all i*j
 * cells in the sub rectangle are 1.
 *
 * cnt[0][j] and cnt[i][0] will contain garbage values.
 * @time O(n * m)
 * @memory O(n * m)
 */
vector<vector<int>> count_rectangles(const vector<vector<bool>>& grid) {
	int n = ssize(grid), m = ssize(grid[0]);
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
			int le = j - left[j] - 1, ri = rv(right[rv(j)]) - j - 1;
			cnt[arr[j]][le + ri + 1]++;
			cnt[arr[j]][le]--;
			cnt[arr[j]][ri]--;
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
