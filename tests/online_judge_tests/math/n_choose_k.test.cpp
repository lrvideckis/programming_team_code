#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_E"
#include "../template.hpp"
#include "../../../library/math/binary_exponentiation_mod.hpp"

#include "../../../library/math/n_choose_k_mod.hpp"

template<int N> void test_lucas(const n_choose_k<N>& choose_l) {
	const int MAX_N = 1000;
	assert(N < MAX_N);
	vector<vector<long long>> naive_choose(MAX_N, vector<long long>(MAX_N, 0));
	for (int i = 0; i < MAX_N; i++) {
		naive_choose[i][0] = 1;
		for (int j = 1; j <= i; j++)
			naive_choose[i][j] = (naive_choose[i - 1][j] + naive_choose[i - 1][j - 1]) % N;
	}
	for (int i = 0; i < MAX_N; i++) {
		assert(choose_l.choose_lucas(i, -1) == 0);
		assert(choose_l.choose_lucas(i, i + 1) == 0);
		assert(choose_l.choose_lucas(-1, i) == 0);
		assert(choose_l.choose_lucas(i, i - 1) == i % N);
		for (int j = 0; j < MAX_N; j++)
			assert(choose_l.choose_lucas(i, j) == naive_choose[i][j]);
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	//test choose with lucas theorem
	test_lucas<2>(n_choose_k<2>(2));
	test_lucas<3>(n_choose_k<3>(3));
	test_lucas<5>(n_choose_k<5>(5));
	test_lucas<7>(n_choose_k<7>(7));
	test_lucas<11>(n_choose_k<11>(11));
	test_lucas<13>(n_choose_k<13>(13));
	const int N = 1001, MOD = 1e9 + 7;
	n_choose_k<MOD> nk(N);
	//test mod inverse
	for (int i = 1; i < N; i++)
		assert(nk.inv[i] == bin_exp(i, MOD - 2, MOD));
	int balls, boxes;
	cin >> balls >> boxes;
	//you have to choose the subset of boxes to place balls into
	cout << nk.choose(boxes, balls) << '\n';
	return 0;
}
