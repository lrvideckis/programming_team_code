#pragma once

//status: tested on random inputs

//returns base^pw % mod in O(log(pw))
//returns 1 for 0^0
int fastPow(long long base, long long pw, int mod) {
	assert(0 <= pw && 0 <= base && 1 <= mod);
	int res = 1;
	base %= mod;
	while (pw > 0) {
		if (pw & 1) res = 1LL * res * base % mod;
		base = 1LL * base * base % mod;
		pw >>= 1;
	}
	return res;
}
