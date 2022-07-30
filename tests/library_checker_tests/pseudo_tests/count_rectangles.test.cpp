#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "../../template.h"
#include "../../random.h"

#include "../../../library/misc/count_rectangles.h"

int main() {
	for (int tests = 20; tests--;) {
		int n = get_rand(1, 100), m = get_rand(1, 100);
		vector<vector<bool>> grid(n, vector<bool>(m));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				grid[i][j] = (get_rand(1, 3) == 1);
		}
		vector<vector<int>> prefix(n + 1, vector<int>(m + 1, 0));
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++)
				prefix[i][j] = grid[i - 1][j - 1] + prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
		}
		vector<vector<int>> naive(n + 1, vector<int>(m + 1, 0));
		for (int i1 = 1; i1 <= n; i1++) {
			for (int i2 = i1; i2 <= n; i2++) {
				for (int j1 = 1; j1 <= m; j1++) {
					for (int j2 = j1; j2 <= m; j2++) {
						int cnt = prefix[i2][j2] - prefix[i1 - 1][j2] - prefix[i2][j1 - 1] + prefix[i1 - 1][j1 - 1];
						if (cnt == (i2 - i1 + 1) * (j2 - j1 + 1))
							naive[i2 - i1 + 1][j2 - j1 + 1]++;
					}
				}
			}
		}
		vector<vector<int>> fast = count_rectangles(grid);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++)
				assert(naive[i][j] == fast[i][j]);
		}
	}
	int a, b;
	cin >> a >> b;
	cout << a + b << endl;
	return 0;
}
