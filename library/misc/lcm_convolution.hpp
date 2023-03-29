/** @file */
#pragma once
/**
 * @author camc
 * @param a,b arrays of the same length
 * @returns array `c` where `c[k]` = the sum of (a[i] * b[j]) for all pairs
 * (i,j) where lcm(i,j) == k
 * @time O(n log n)
 * @memory O(n)
 */
template<int MOD> vector<int> lcm_convolution(const vector<int>& a, const vector<int>& b) {
	assert(ssize(a) == ssize(b));
	int n = ssize(a);
	vector<int> sum_a(n), sum_b(n), c(n);
	for (int i = 1; i < n; i++) {
		for (int j = i; j < n; j += i)
			sum_a[j] = (sum_a[j] + a[i]) % MOD, sum_b[j] = (sum_b[j] + b[i]) % MOD;
		c[i] = int((1LL * sum_a[i] * sum_b[i]) % MOD);
	}
	for (int i = 1; i < n; i++)
		for (int j = i + i; j < n; j += i)
			c[j] = (c[j] - c[i] + MOD) % MOD;
	return c;
}
