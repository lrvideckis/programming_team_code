#pragma once

//given a 2D boolean matrix, calculate cnt[i][j]
//cnt[i][j] = the number of times an (i * j) rectangle appears in the matrix
//such that all cells in the rectangle are false
//Note cnt[0][j] and cnt[i][0] will contain garbage values
//O(R*C)
//
//status: tested on random inputs
vector<vector<int>> getNumRectangles(const vector<vector<bool>>& grid) {
	vector<vector<int>> cnt;
	const int rows = grid.size(), cols = grid[0].size();
	if (rows == 0 || cols == 0) return cnt;
	cnt.resize(rows + 1, vector<int> (cols + 1, 0));
	vector<vector<int>> arr(rows + 2, vector<int> (cols + 1, 0));
	for (int i = 1; i <= rows; ++i) {
		for (int j = 1; j <= cols; ++j) {
			arr[i][j] = 1 + arr[i][j - 1];
			if (grid[i - 1][j - 1]) arr[i][j] = 0;
		}
	}
	for (int j = 1; j <= cols; ++j) {
		arr[rows + 1][j] = 0;
		stack<pair<int, int>> st;
		st.push({0, 0});
		for (int i = 1; i <= rows + 1; ++i) {
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
	for (int j = 1; j <= cols; ++j) {
		for (int i = rows - 1; i >= 1; --i)
			cnt[i][j] += cnt[i + 1][j];
		for (int i = rows - 1; i >= 1; --i)
			cnt[i][j] += cnt[i + 1][j];
	}
	for (int i = 1; i <= rows; ++i) {
		for (int j = cols - 1; j >= 1; --j)
			cnt[i][j] += cnt[i][j + 1];
	}
	return cnt;
}
