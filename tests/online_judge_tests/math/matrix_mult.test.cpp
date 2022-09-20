#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"
#include "../../template.hpp"

#include "../../../library/math/matrix_mult.hpp"
#include "../../../ac-library/atcoder/modint.hpp"

const int MOD = 998'244'353;
istream& operator >> (istream& is, atcoder::static_modint<MOD>& mint) {
	int x;
	is >> x;
	mint = x;
	return is;
}

ostream& operator << (ostream& os, atcoder::static_modint<MOD> mint) {
	return os << mint.val();
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k;
	cin >> n >> m >> k;
	vector<vector<atcoder::static_modint<MOD>>> m1(n, vector<atcoder::static_modint<MOD>>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cin >> m1[i][j];
	}
	vector<vector<atcoder::static_modint<MOD>>> m2(m, vector<atcoder::static_modint<MOD>>(k));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < k; j++)
			cin >> m2[i][j];
	}
	auto prod = m1 * m2;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++)
			cout << prod[i][j] << " ";
		cout << '\n';
	}
	return 0;
}