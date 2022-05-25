#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"
#include "../../template.h"

#include "../../../Library/math/row_reduce.h"

int main() {
	cin.tie(0)->sync_with_stdio(false);

	int n;
	cin >> n;

	vector<vector<int>> matrix(n, vector<int>(n));
	for(int i= 0; i < n; i++) {
		for(int j= 0; j < n; j++) {
			cin >> matrix[i][j];
		}
	}

	auto [rank, det] = row_reduce(matrix, b, 998244353);

	cout << det << endl;
	return 0;
}
