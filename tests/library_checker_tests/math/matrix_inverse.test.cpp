#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix"
#include "../../template.h"

#include "../../../library/math/matrix_inverse.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	vector<vector<int>> matrix(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cin >> matrix[i][j];
	}
	matrix = matrix_inverse(matrix, 998244353);
	if (matrix.empty()) {
		cout << -1 << endl;
		return 0;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
	return 0;
}
