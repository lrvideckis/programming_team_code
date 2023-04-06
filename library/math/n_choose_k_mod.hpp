/** @file */
#pragma once
const int N = 1001;
long long inv[N], fact[N], inv_fact[N];
/**
 * @time O(N + sqrt(MOD))
 * @memory O(N)
 */
template<int MOD> void calc_chooses() {
	for (int i = 2; i * i <= MOD; i++) assert(MOD % i);
	for (int i = 0; i < 2; i++)
		inv[i] = fact[i] = inv_fact[i] = 1;
	for (int i = 2; i < N; i++) {
		inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
		fact[i] = fact[i - 1] * i % MOD;
		inv_fact[i] = inv_fact[i - 1] * inv[i] % MOD;
	}
}
/**
 * @param n,k requires n < N
 * @returns number of ways to choose k objects out of n
 * @time O(1)
 */
//NOLINTNEXTLINE(readability-identifier-naming)
template<int MOD> long long C(int n, int k) {
	if (k < 0 || n < k) return 0;
	return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}
/**
 * requires O(MOD) precalc
 * @param n,k arbitrarily large integers
 * @returns number of ways to choose k objects out of n
 * @time O(log(k))
 */
//NOLINTNEXTLINE(readability-identifier-naming)
template<int MOD> long long C(long long n, long long k) {
	if (k < 0 || n < k) return 0;
	long long res = 1;
	for (; k && k < n && res; n /= MOD, k /= MOD)
		res = res * C<MOD>(int(n % MOD), int(k % MOD)) % MOD;
	return res;
}