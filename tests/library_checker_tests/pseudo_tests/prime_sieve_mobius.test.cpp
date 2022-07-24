#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "../../template.h"

#include "../../../library/math/prime_sieve_mobius.h"

//kactl is_prime
typedef long long ll;
typedef unsigned long long ull;
ull modmul(ull a, ull b, const ull M) {
	ll ret = a * b - M * ull(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}
bool is_prime(ull n) {
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
	    s = __builtin_ctzll(n-1), d = n >> s;
	for (ull a : A) {   // ^ count trailing zeroes
		ull p = modpow(a%n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = modmul(p, p, n);
		if (p != n-1 && i != s) return 0;
	}
	return 1;
}

int main() {
	calc_mobius();
	calc_seive();

	for(int i = 2; i < N; i++) {
		assert(is_prime(i) == (a_prime[i] == i));
		assert(is_prime(a_prime[i]));
		assert(i % a_prime[i] == 0);
		int val = i;
		map<int,int> prime_power;
		while(val > 1) {
			int p = a_prime[val];
			prime_power[p]++;
			val /= p;
		}
		bool found_square = false;
		for(auto [prime, exp] : prime_power) {
			if(exp >= 2) found_square = true;
		}
		if(found_square) {
			assert(mobius[i] == 0);
		} else if(prime_power.size()%2 == 0) {
			assert(mobius[i] == 1);
		} else {
			assert(mobius[i] == -1);
		}
	}

	int a, b;
	cin >> a >> b;
	cout << a + b << endl;
	return 0;
}
