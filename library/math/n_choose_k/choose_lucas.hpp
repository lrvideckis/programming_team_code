/** @file */
#pragma once
#include "n_choose_k.hpp"
/**
 * requires O(MOD) precalc
 * @param n,k arbitrarily large integers
 * @returns number of ways to choose k objects out of n
 * @time O(log(k))
 * @space O(1)
 */
//NOLINTNEXTLINE(readability-identifier-naming)
long long C(long long n, long long k) {
    static_assert(MOD <= N);
    if (k < 0 || n < k) return 0;
    long long res = 1;
    for (; k && k < n && res; n /= MOD, k /= MOD)
        res = res * C(int(n % MOD), int(k % MOD)) % MOD;
    return res;
}
