#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_E"
#include "../template.hpp"
#include "../../../library/math/prime_sieve.hpp"
#include "../../../library/math/binary_exponentiation_mod.hpp"

#include "../../../library/math/n_choose_k_mod.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	const int N = 1001, MOD = 1e9 + 7;
	{
		//test choose with lucas theorem
		vector<int> sieve = get_sieve(N);
		vector<vector<long long>> naive_choose(100, vector<long long>(100, 0));
		int num_primes = 0;
		for (int mod = 2; mod < 100; mod++) {
			if (!is_prime(mod, sieve)) continue;
			n_choose_k<mod> choose_l(mod);
			num_primes++;
			for (int n = 0; n < 100; n++) {
				naive_choose[n][0] = 1;
				for (int k = 1; k <= n; k++)
					naive_choose[n][k] = (naive_choose[n - 1][k] + naive_choose[n - 1][k - 1]) % mod;
			}
			for (int n = 0; n < 100; n++) {
				assert(choose_l.choose_lucas(n, -1) == 0);
				assert(choose_l.choose_lucas(n, n + 1) == 0);
				assert(choose_l.choose_lucas(-1, n) == 0);
				for (int k = 0; k < 100; k++)
					assert(choose_l.choose_lucas(n, k) == naive_choose[n][k]);
			}
		}
		assert(num_primes == 25);
	}
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
