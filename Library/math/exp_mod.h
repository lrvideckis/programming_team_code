#pragma once

//status: tested on random inputs

//returns a^pw % mod in O(log(pw))
long long fastPow(long long a, long long pw, int mod) {
	long long res = 1;
	a %= mod;
	while (pw > 0) {
		if (pw & 1) res = (res * a) % mod;
		a = (a * a) % mod;
		pw >>= 1;
	}
	return res;
}
