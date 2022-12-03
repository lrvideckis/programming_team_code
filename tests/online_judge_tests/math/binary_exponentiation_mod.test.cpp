#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_B"
#include "../template.hpp"

#include "../../../library/math/binary_exponentiation_mod.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int m, n;
	cin >> m >> n;
	cout << bin_exp(m, n, 1e9 + 7) << '\n';
	return 0;
}
