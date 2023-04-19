/** @file */
#pragma once
const int MOD = 998'244'353;
/**
 * @see https://github.com/kth-competitive-programming/kactl
 * /blob/main/content/number-theory/ModPow.h
 * @param b base
 * @param e exponent
 * @returns (b^e)%MOD, 1 for 0^0.
 * @time O(log e)
 */
long long bin_exp(long long b, long long e) {
    assert(0 <= e);
    long long res = 1;
    if ((b %= MOD) < 0) b += MOD;
    for (; e; b = b * b % MOD, e /= 2)
        if (e & 1) res = res * b % MOD;
    return res;
}
