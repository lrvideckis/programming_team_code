#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/math/prime_sieve.hpp"

#include "../../../library/math/mobius_inversion.hpp"

int main() {
	calc_sieve();
	calc_mobius();
	for (int i = 1; i < min(N, MX_N); i++) {
		int val = i;
		map<int, int> factors;
		while (val > 1) {
			int p = a_prime[val];
			//p is some prime factor of val
			factors[p]++;
			val /= p;
		}
		{
			bool found_square = 0;
			for (auto [prime, exponent] : factors) {
				if (exponent > 1) {
					assert(mobius[i] == 0);
					found_square = 1;
					break;
				}
			}
			if (found_square) continue;
		}
		assert(1 - 2 * (int(factors.size()) % 2) == mobius[i]);
	}
	cout << "Hello World\n";
	return 0;
}
