#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"
#include "../../stress-tests/test_utilities/template.h"

#include "../../../Library/math/solve_linear_mod.h"

int main() {
	cin.tie(0)->sync_with_stdio(false);

	const int mod = 998244353;

	int n;
	cin >> n;

	vector<vector<int>> matrix(n, vector<int>(n));
	for(int i= 0; i < n; i++) {
		for(int j= 0; j < n; j++) {
			cin >> matrix[i][j];
		}
	}

	vector<int> b(n);
	matrixInfo info = solve_linear_mod(matrix, b, mod);

	cout << info.det << endl;
	return 0;
}
