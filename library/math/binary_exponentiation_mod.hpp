/** @file */
#pragma once
const int MOD = 998'244'353;
/**
 * @param base,pw see return
 * @returns (base^pw)%MOD, 1 for 0^0.
 * @time O(log pw)
 */
long long bin_exp(long long base, long long pw) {
	assert(0 <= pw && 1 <= MOD);
	long long res = 1;
	base %= MOD;
	if (base < 0) base += MOD;
	while (pw > 0) {
		if (pw & 1) res = res * base % MOD;
		base = base * base % MOD;
		pw >>= 1;
	}
	return res;
}
