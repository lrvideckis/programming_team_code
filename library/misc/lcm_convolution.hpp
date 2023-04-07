/** @file */
#pragma once
const int mod = 998'244'353; //TODO change to MOD, this is to test that the CI catches it
/**
 * @author camc
 * @param a,b arrays of the same length
 * @returns array `c` where `c[k]` = the sum of (a[i] * b[j]) for all pairs
 * (i,j) where lcm(i,j) == k
 * @time O(n log n)
 * @memory O(n)
 */
vector<int> lcm_convolution(const vector<int>& a, const vector<int>& b) {
	assert(ssize(a) == ssize(b));
	int n = ssize(a);
	vector<long long> sum_a(n), sum_b(n);
	vector<int> c(n);
	for (int i = 1; i < n; i++) {
		for (int j = i; j < n; j += i)
			sum_a[j] += a[i], sum_b[j] += b[i];
		c[i] = int(sum_a[i] % mod * (sum_b[i] % mod) % mod);
	}
	for (int i = 1; i < n; i++)
		for (int j = i + i; j < n; j += i)
			c[j] = (c[j] - c[i] + mod) % mod;
	return c;
}
