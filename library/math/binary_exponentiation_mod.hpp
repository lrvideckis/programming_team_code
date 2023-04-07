/** @file */
#pragma once
const int MOD = 998'244'353;
/**
 * @param b base
 * @param e exponent
 * @returns (b^e)%MOD, 1 for 0^0.
 * @time O(log pw)
 */
long long bin_exp(long long b, long long e) {
	assert(0 <= e);
	long long res = 1;
	if ((b %= MOD) < 0) b += MOD;
	for (; e; b = b * b % MOD, e /= 2)
		if (e & 1) res = res * b % MOD;
	return res;
}
