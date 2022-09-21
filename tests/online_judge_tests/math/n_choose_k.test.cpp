#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_E"
#include "../template.hpp"
#include "../../../library/math/prime_sieve.hpp"

#include "../../../library/math/n_choose_k_mod.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	const int MOD = 1e9 + 7;
	n_choose_k nk(1001, MOD);
	//test mod inverse
	{
		//source: https://codeforces.com/blog/entry/83075
		vector<int> inverse(1001);
		inverse[1] = 1;
		for (int i = 2; i < (int)inverse.size(); i ++)
			inverse[i] = 1LL * (MOD - MOD / i) * inverse[MOD % i] % MOD;
		for (int i = 1; i < (int)inverse.size(); i ++)
			assert(nk.inv(i) == inverse[i]);
	}
	{
		//test choose with lucas theorem
		vector<int> sieve = get_sieve(1001);
		vector<vector<int>> naive_choose(100, vector<int>(100, 0));
		int num_primes = 0;
		for (int mod = 2; mod < 100; mod++) {
			if (is_prime(mod, sieve)) {
				n_choose_k choose_l(mod, mod);
				num_primes++;
				for (int n = 0; n < 100; n++) {
					naive_choose[n][0] = 1;
					for (int k = 1; k <= n; k++)
						naive_choose[n][k] = (naive_choose[n - 1][k] + naive_choose[n - 1][k - 1]) % mod;
				}
				for (int n = 0; n < 100; n++) {
					for (int k = 0; k < 100; k++)
						assert(choose_l.choose_lucas(n, k) == naive_choose[n][k]);
				}
			}
		}
		assert(num_primes == 25);
	}
	int balls, boxes;
	cin >> balls >> boxes;
	//you have to choose the subset of boxes to place balls into
	cout << nk.choose(boxes, balls) << '\n';
	return 0;
}
