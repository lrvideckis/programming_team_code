#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_3_B"
#include "../../../kactl/stress-tests/utilities/template.h"
#include "../../../kactl/content/data-structures/SubMatrix.h"
#include "../../../library/misc/random.hpp"

#include "../../../library/misc/monotonic_stack_related/count_rectangles.hpp"

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
	{
		vector<vector<int>> temp_grid(n, vector<int>(m));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				temp_grid[i][j] = grid[i][j];
		}
		SubMatrix<int> sm(temp_grid);
		int tests = 20;
		while (tests--) {
			int rows = get_rand(1, n + 1), cols = get_rand(1, m + 1);
			int cnt = 0;
			for (int i = 0; i + rows <= n; i++) {
				for (int j = 0; j + cols <= m; j++) {
					if (sm.sum(i, j, i + rows, j + cols) == rows * cols) cnt++;
				}
			}
			assert(size_counts[rows][cols] == cnt);
		}
	}
	int res = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (size_counts[i][j]) res = max(res, i * j);
		}
	}
	cout << res << '\n';
	return 0;
}
