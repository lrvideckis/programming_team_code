#pragma once
//stress tests: tests/stress-tests/misc/cntRectangles.cpp

//given a 2D boolean matrix, calculate cnt[i][j]
//cnt[i][j] = the number of times an (i * j) rectangle appears in the matrix
//such that all cells in the rectangle are false
//Note cnt[0][j] and cnt[i][0] will contain garbage values
//O(R*C)
vector<vector<int>> getNumRectangles(const vector<vector<bool>>& grid) {
	const int n = grid.size(), m = grid[0].size();
	vector<vector<int>> cnt(n + 1, vector<int>(m + 1, 0)), arr(n + 2, vector<int>(m + 1, 0));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			arr[i][j] = 1 + arr[i][j - 1];
			if (grid[i - 1][j - 1]) arr[i][j] = 0;
		}
	}
	for (int j = 1; j <= m; j++) {
		arr[n + 1][j] = 0;
		stack<pair<int, int>> st;
		st.push({0, 0});
		for (int i = 1; i <= n + 1; i++) {
			pair<int, int> curr = {i, arr[i][j]};
			while (arr[i][j] < st.top().second) {
				curr = st.top();
				st.pop();
				cnt[i - curr.first][curr.second]++;
				cnt[i - curr.first][max(arr[i][j], st.top().second)]--;
			}
			st.push({curr.first, arr[i][j]});
		}
	}
	for (int j = 1; j <= m; j++) {
		for (int k = 0; k < 2; k++) {
			for (int i = n - 1; i >= 1; i--)
				cnt[i][j] += cnt[i + 1][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = m - 1; j >= 1; j--)
			cnt[i][j] += cnt[i][j + 1];
	}
	return cnt;
}
