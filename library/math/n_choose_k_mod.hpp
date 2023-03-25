/** @file */
#pragma once
/**
 * @code{.cpp}
 *     n_choose_k<1'000'000'007> nk(n); // to use `choose` with inputs strictly < n
 *     n_choose_k<1'000'003> nk(1'000'003); // to use `choose_lucas` with arbitrarily large inputs
 * @endcode
 *
 * @tparam MOD a prime > n
 */
template<int MOD> struct n_choose_k {
	vector<long long> inv, fact, inv_fact;
	/**
	 * @param n size
	 * @time O(n + sqrt(MOD))
	 * @memory O(n)
	 */
	n_choose_k(int n) : inv(n, 1), fact(n, 1), inv_fact(n, 1) {
		assert(max(n, 2) <= MOD);
		for (int i = 2; i * i <= MOD; i++) assert(MOD % i);
		for (int i = 2; i < n; i++) {
			inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
			fact[i] = fact[i - 1] * i % MOD;
			inv_fact[i] = inv_fact[i - 1] * inv[i] % MOD;
		}
	}
	/**
	 * @param n,k requires n < ssize(fact)
	 * @returns number of ways to choose k objects out of n
	 * @time O(1)
	 */
	long long choose(int n, int k) const {
		if (k < 0 || n < k) return 0;
		return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
	}
	/**
	 * @param n,k arbitrarily large integers
	 * @returns number of ways to choose k objects out of n
	 * @time O(log(k))
	 */
	long long choose_lucas(long long n, long long k) const {
		if (k < 0 || n < k) return 0;
		long long res = 1;
		for (; k && k < n && res; n /= MOD, k /= MOD)
			res = res * choose(int(n % MOD), int(k % MOD)) % MOD;
		return res;
	}
};
