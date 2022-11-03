#pragma once
#include "binary_exponentiation_mod.hpp"
/**
 * @file
 * @brief N Choose K
 * @code{.cpp}
 *     n_choose_k nk(n, 1e9+7); // to use `choose`, `inv` with inputs strictly < n
 *     n_choose_k nk(mod, mod); // to use `choose_lucas` with arbitrarily large inputs
 * @endcode
 */
struct n_choose_k {
	/**
	 * @note Only works for `n <= mod` and prime mod.
	 * @time O(n + sqrt(mod))
	 * @memory O(n)
	 */
	n_choose_k(int n, long long a_mod) : mod(a_mod), fact(n, 1), inv_fact(n, 1) {
		assert(max(n, 2) <= mod);
		for (int i = 2; i * i <= mod; i++)
			assert(mod % i);
		for (int i = 2; i < n; i++)
			fact[i] = fact[i - 1] * i % mod;
		inv_fact.back() = bin_exp(fact.back(), mod - 2, mod);
		for (int i = n - 2; i >= 2; i--)
			inv_fact[i] = inv_fact[i + 1] * (i + 1) % mod;
	}
	/**
	 * @brief Classic n choose k, fails when n >= mod.
	 * @time O(1)
	 */
	long long choose(int n, int k) const {
		if (k < 0 || k > n)
			return 0;
		//now we know 0 <= k <= n so 0 <= n
		return fact[n] * inv_fact[k] % mod * inv_fact[n - k] % mod;
	}
	/**
	 * @brief Lucas theorem - n choose k for n, k up to LLONG_MAX. Handles n >=
	 * mod correctly.
	 * @time O(log(k))
	 * @memory O(mod) precomp needed, so can't use 1e9 + 7.
	 */
	long long choose_lucas(long long n, long long k) const {
		if (k < 0 || k > n)
			return 0;
		if (k == 0 || k == n)
			return 1;
		return choose_lucas(n / mod, k / mod) * choose(int(n % mod), int(k % mod)) % mod;
	}
	/**
	 * @brief Returns x such that x * n % mod == 1.
	 * @time O(1)
	 */
	long long inv(int n) const {
		assert(1 <= n); //don't divide by 0 :)
		return fact[n - 1] * inv_fact[n] % mod;
	}
	long long mod;
	vector<long long> fact, inv_fact;
};
