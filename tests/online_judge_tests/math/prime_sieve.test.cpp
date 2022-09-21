#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_C"
#include "../template.hpp"

#include "../../../library/math/prime_sieve.hpp"

int main() {
	vector<int> sieve = get_sieve(1001);
	int n;
	cin >> n;
	map<int, int> prime_to_max_exponent;
	while (n--) {
		int val;
		cin >> val;
		map<int, int> curr;
		for (int prime_factor : get_prime_factors(val, sieve))
			curr[prime_factor]++;
		for (auto [p, e] : curr)
			prime_to_max_exponent[p] = max(prime_to_max_exponent[p], e);
	}
	int res = 1;
	for (auto [p, e] : prime_to_max_exponent) {
		while (e--) res *= p;
	}
	cout << res << '\n';
	return 0;
}
