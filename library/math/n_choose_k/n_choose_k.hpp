/** @file */
#pragma once
const int mx_n = 17, mod = 17;
long long inv[mx_n], fact[mx_n], inv_fact[mx_n];
/**
 * @time O(mx_n + sqrt(mod))
 * @space O(mx_n)
 */
void calc_facts() {
    static_assert(max(2, mx_n) <= mod);
    for (int i = 2; i * i <= mod; i++) assert(mod % i);
    for (int i = 0; i < 2; i++)
        inv[i] = fact[i] = inv_fact[i] = 1;
    for (int i = 2; i < mx_n; i++) {
        inv[i] = mod - (mod / i) * inv[mod % i] % mod;
        fact[i] = fact[i - 1] * i % mod;
        inv_fact[i] = inv_fact[i - 1] * inv[i] % mod;
    }
}
/**
 * @param n,k requires n < mx_n
 * @returns number of ways to choose k objects out of n
 * @time O(1)
 * @space O(1)
 */
//NOLINTNEXTLINE(readability-identifier-naming)
inline long long C(int n, int k) {
    assert(fact[n]);
    if (k < 0 || n < k) return 0;
    return fact[n] * inv_fact[k] % mod * inv_fact[n - k] % mod;
}
