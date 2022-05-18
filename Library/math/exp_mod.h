#pragma once

//status: tested on random inputs

//returns base^pw % mod in O(log(pw))
//returns 1 for 0^0
//for powers > INT_MAX, do: pw %= totient(mod) if gcd(base, mod) == 1 else switch `pw` to long long
int fastPow(int base, int pw, int mod) {
	assert(0 <= pw && 0 <= base && 1 <= mod);
	int res = 1;
	while (pw > 0) {
		if (pw & 1) res = 1LL * res * base % mod;
		base = 1LL * base * base % mod;
		pw >>= 1;
	}
	return res;
}
