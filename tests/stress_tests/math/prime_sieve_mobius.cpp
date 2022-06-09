#include "../../template.h"

#include "../../../Library/math/primeSieveMobius.h"

//kactl isPrime
typedef long long ll;
typedef unsigned long long ull;
ull modmul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}
bool isPrime(ull n) {
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
	calcMobius();
	calcSeive();

	for(int i = 2; i < N; i++) {
		assert(isPrime(i) == (aPrime[i] == i));
		assert(isPrime(aPrime[i]));
		assert(i % aPrime[i] == 0);
		int val = i;
		map<int,int> primePower;
		while(val > 1) {
			int p = aPrime[val];
			primePower[p]++;
			val /= p;
		}
		bool foundSquare = false;
		for(auto [prime, exp] : primePower) {
			if(exp >= 2) foundSquare = true;
		}
		if(foundSquare) {
			assert(mobius[i] == 0);
		} else if(primePower.size()%2 == 0) {
			assert(mobius[i] == 1);
		} else {
			assert(mobius[i] == -1);
		}
	}

	cout << "Tests passed!" << endl;
	return 0;
}
