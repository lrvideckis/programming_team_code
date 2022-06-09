#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"
#include "../../template.h"

#include "../../../library/math/matrix_expo.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k;
	cin >> n >> m >> k;
	vector<vector<int>> m1(n, vector<int>(m));
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			cin >> m1[i][j];
		}
	}
	vector<vector<int>> m2(m, vector<int>(k));
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < k; j++) {
			cin >> m2[i][j];
		}
	}
	vector<vector<int>> prod = mult(m1, m2, 998244353);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < k; j++) {
			cout << prod[i][j] << " ";
		}
		cout << '\n';
	}
	return 0;
}
