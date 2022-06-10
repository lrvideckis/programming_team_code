#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations"
#include "../../template.h"

#include "../../../library/math/solve_linear_mod.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);

	const int mod = 998244353;

	int n, m;
	cin >> n >> m;

	vector<vector<int>> A(n, vector<int>(m));
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			cin >> A[i][j];
		}
	}

	vector<int> b(n);
	for(int i = 0; i < n; i++) {
		cin >> b[i];
	}

	matrix_info info = solve_linear_mod(A, b, mod);

	if(info.x.empty()) {
		cout << -1 << endl;
		return 0;
	}

	cout << m - info.rank << endl;

	for(int val : info.x) cout << val << " ";
	cout << endl;

	vector<int> pivot(m, -1);
	for (int i = 0, j = 0; i < info.rank; ++i) {
		while (A[i][j] == 0) ++j;
		pivot[j] = i;
	}
	for (int j = 0; j < m; ++j) if (pivot[j] == -1) {
		vector<int> x(m, 0);
		x[j] = mod-1;
		for (int k = 0; k < j; ++k) if (pivot[k] != -1) x[k] = A[pivot[k]][j];

		for (int k = 0; k < m; ++k) cout << x[k] << " ";
		cout << endl;
	}
	return 0;
}
