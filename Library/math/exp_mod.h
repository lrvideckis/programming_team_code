#pragma once

//status: tested on random inputs

//returns a^pw % mod in O(log(pw))
int fastPow(int a, long long pw, int mod) {
	assert(0 <= pw && 0 <= a && a < mod);
	int res = 1;
	while (pw > 0) {
		if (pw & 1) res = 1LL * res * a % mod;
		a = 1LL * a * a % mod;
		pw >>= 1;
	}
	return res;
}
