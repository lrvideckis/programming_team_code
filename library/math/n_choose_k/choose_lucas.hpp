/** @file */
#pragma once
#include "n_choose_k.hpp"
/**
 * @param n,k arbitrarily large integers
 * @returns number of ways to choose k objects out of n
 * @time O(log(k)) amortized
 * @space O(1) amortized
 */
//NOLINTNEXTLINE(readability-identifier-naming)
long long C(long long n, long long k) {
    if (k < 0 || n < k) return 0;
    auto res = 1LL;
    for (; k && k < n && res; n /= mod, k /= mod)
        res = res * C(int(n % mod), int(k % mod)) % mod;
    return res;
}
