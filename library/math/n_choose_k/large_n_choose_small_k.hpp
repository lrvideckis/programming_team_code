/** @file */
#pragma once
#include "factorial.hpp"
/**
 * @param n arbitrarily large integer; n - k < mod < n is ok
 * @param k integer with k < mod
 * @returns number of ways to choose k objects out of n
 * @time O(k)
 * @space O(1) ammortized
 */
inline int64_t c_small_k(int64_t n, int k) {
	if (k < 0 || n < k) return 0;
	grow(k);
	auto res = inv_fact[k];
	for (int64_t i = n; i > n - k && res; i--) res = i % mod * res % mod;
	return res;
}
