/** @file */
#pragma once
const int mod = 998'244'353;
/**
 * @see https://github.com/kth-competitive-programming/kactl /blob/main/content/number-theory/ModPow.h
 * @param b base
 * @param e exponent
 * @returns (b^e)%mod, 1 for 0^0.
 * @time O(log e)
 * @space O(1)
 */
long long bin_exp(long long b, long long e) {
    assert(0 <= e);
    long long res = 1;
    if ((b %= mod) < 0) b += mod;
    for (; e; b = b * b % mod, e /= 2)
        if (e & 1) res = res * b % mod;
    return res;
}
