#pragma once
/**
 * Returns (base^pw)%mod; returns 1 for 0^0.
 * @time O(log pw)
 */
long long bin_exp(long long base, long long pw, long long mod) {
	assert(0 <= pw && 0 <= base && 1 <= mod);
	long long res = 1;
	base %= mod;
	while (pw > 0) {
		if (pw & 1) res = res * base % mod;
		base = base * base % mod;
		pw >>= 1;
	}
	return res;
}
