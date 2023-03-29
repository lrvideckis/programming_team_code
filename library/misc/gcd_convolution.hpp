/** @file */
#pragma once
/**
 * @param a,b arrays of the same length
 * @returns array `c` where `c[k]` = the sum of (a[i] * b[j]) for all pairs
 * (i,j) where gcd(i,j) == k
 * @time O(n log n)
 * @memory O(n)
 */
template<int MOD> vector<int> gcd_convolution(const vector<int>& a, const vector<int>& b) {
	assert(ssize(a) == ssize(b));
	int n = ssize(a);
	vector<int> c(n);
	for (int g = n - 1; g >= 1; g--) {
		int sum_a = 0, sum_b = 0;
		for (int i = g; i < n; i += g) {
			sum_a = (sum_a + a[i]) % MOD, sum_b = (sum_b + b[i]) % MOD;
			c[g] = (c[g] - c[i] + MOD) % MOD;
		}
		c[g] = int((c[g] + 1LL * sum_a * sum_b) % MOD);
	}
	return c;
}
