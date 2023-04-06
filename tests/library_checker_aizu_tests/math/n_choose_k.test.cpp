#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_E"
#include "../template.hpp"
#include "../../../library/math/binary_exponentiation_mod.hpp"

#include "../../../library/math/n_choose_k_mod.hpp"

template<int MOD> void test_lucas() {
	calc_chooses<MOD>();
	vector<vector<long long>> naive_choose(N, vector<long long>(N, 0));
	for (int i = 0; i < N; i++) {
		naive_choose[i][0] = 1;
		for (int j = 1; j <= i; j++)
			naive_choose[i][j] = (naive_choose[i - 1][j] + naive_choose[i - 1][j - 1]) % MOD;
	}
	for (int i = 0; i < N; i++) {
		assert(C<MOD>(1LL * i, -1LL) == 0);
		assert(C<MOD>(1LL * i, 1LL * i + 1) == 0);
		assert(C<MOD>(-1LL, 1LL * i) == 0);
		assert(C<MOD>(1LL * i, 1LL * i - 1) == i % MOD);
		for (int j = 0; j < N; j++)
			assert(C<MOD>(1LL * i, 1LL * j) == naive_choose[i][j]);
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	//test choose with lucas theorem
	test_lucas<2>();
	test_lucas<3>();
	test_lucas<5>();
	test_lucas<7>();
	test_lucas<11>();
	test_lucas<13>();
	const int MOD = 1'000'000'007;
	calc_chooses<MOD>();
	//test mod inverse
	for (int i = 1; i < N; i++)
		assert(inv[i] == bin_exp(i, MOD - 2, MOD));
	int balls, boxes;
	cin >> balls >> boxes;
	//you have to choose the subset of boxes to place balls into
	cout << C<MOD>(boxes, balls) << '\n';
	return 0;
}
