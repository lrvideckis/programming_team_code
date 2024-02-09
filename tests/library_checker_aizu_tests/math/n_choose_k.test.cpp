#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod"
#include "../template.hpp"

// trick to remove const so I can use arbitrary prime mode here
#define const long
#include "../../../library/math/n_choose_k/n_choose_k.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int t;
	cin >> t >> mod;
	while (t--) {
		int n, k;
		cin >> n >> k;
		cout << C(n, k) << '\n';
		assert(ssize(inv) == ssize(fact) && ssize(inv_fact) == ssize(fact));
	}
	for (int i = 0; i < ssize(inv); i++) {
		if (i) assert(i * inv[i] % mod == 1);
		assert(fact[i] * inv_fact[i] % mod == 1);
	}
	return 0;
}
