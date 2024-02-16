const int mod = 17; /**< must be prime */
vector<long long> inv(2, 1), fact(2, 1), inv_fact(2, 1);
/**
 * @param n,k integers with n < mod
 * @returns number of ways to choose k objects out of n
 * @time O(1) amortized
 * @space O(1) amortized
 */
inline long long C(int n, int k) {
	assert(n < mod);
	if (k < 0 || n < k) return 0;
	while (ssize(inv) <= n) {
		int i = ssize(inv);
		inv.push_back(mod - (mod / i) * inv[mod % i] % mod);
		fact.push_back(i * fact[i - 1] % mod);
		inv_fact.push_back(inv[i] * inv_fact[i - 1] % mod);
	}
	return fact[n] * inv_fact[k] % mod * inv_fact[n - k] % mod;
}
/**
 * @param n,k arbitrarily large integers
 * @returns number of ways to choose k objects out of n
 * @time O(log(k)) amortized
 * @space O(1) amortized
 */
long long C(long long n, long long k) {
	if (k < 0 || n < k) return 0;
	auto res = 1LL;
	for (; k && k < n && res; n /= mod, k /= mod)
		res = res * C(int(n % mod), int(k % mod)) % mod;
	return res;
}
