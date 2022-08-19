#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_3_B"
#include "../../template.h"

#include "../../../library/misc/monotonic_stack_related/count_rectangles.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	vector<vector<bool>> grid(n, vector<bool>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			bool val;
			cin >> val;
			grid[i][j] = !val;
		}
	}
	vector<vector<int>> size_counts = count_rectangles(grid);
	int res = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (size_counts[i][j]) res = max(res, i * j);
		}
	}
	cout << res << '\n';
	return 0;
}
