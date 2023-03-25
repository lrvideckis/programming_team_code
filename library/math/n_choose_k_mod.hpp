/** @file */
#pragma once
/**
 * @code{.cpp}
 *     n_choose_k nk(n, 1e9+7); // to use `choose` with inputs strictly < n
 *     n_choose_k nk(mod, mod); // to use `choose_lucas` with arbitrarily large inputs
 * @endcode
 */
struct n_choose_k {
	long long mod;
	vector<long long> inv, fact, inv_fact;
	/**
	 * @param n size
	 * @param a_mod a prime such that n <= a_mod
	 * @time O(n + sqrt(mod))
	 * @memory O(n)
	 */
	n_choose_k(int n, long long a_mod) : mod(a_mod), inv(n, 1), fact(n, 1), inv_fact(n, 1) {
		assert(max(n, 2) <= mod);
		for (int i = 2; i * i <= mod; i++) assert(mod % i);
		for (int i = 2; i < n; i++) {
			inv[i] = mod - (mod / i) * inv[mod % i] % mod;
			fact[i] = fact[i - 1] * i % mod;
			inv_fact[i] = inv_fact[i - 1] * inv[i] % mod;
		}
	}
	/**
	 * @param n,k requires n < ssize(fact)
	 * @returns number of ways to choose k objects out of n
	 * @time O(1)
	 */
	long long choose(int n, int k) const {
		if (k < 0 || n < k) return 0;
		return fact[n] * inv_fact[k] % mod * inv_fact[n - k] % mod;
	}
	/**
	 * @param n,k arbitrarily large integers
	 * @returns number of ways to choose k objects out of n
	 * @time O(log(k))
	 */
	long long choose_lucas(long long n, long long k) const {
		if (k < 0 || n < k) return 0;
		long long res = 1;
		for (; k && k < n && res; n /= mod, k /= mod)
			res = res * choose(int(n % mod), int(k % mod)) % mod;
		return res;
	}
};
