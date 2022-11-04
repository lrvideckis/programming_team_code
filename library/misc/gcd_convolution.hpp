#pragma once
/**
 * Returns array `c` where `c[k]` = the sum for all pairs where gcd(i,j) == k
 * of a[i] * b[j].
 * @time O(n log n)
 * @memory O(n)
 */
template<int MOD> vector<int> gcd_convolution(const vector<int>& a, const vector<int>& b) {
	assert(ssize(a) == ssize(b));
	int n = ssize(a);
	vector<int> c(n);
	for (int gcd = n - 1; gcd >= 1; gcd--) {
		int sum_a = 0, sum_b = 0;
		for (int i = gcd; i < n; i += gcd) {
			sum_a = (sum_a + a[i]) % MOD, sum_b = (sum_b + b[i]) % MOD;
			c[gcd] = (c[gcd] - c[i] + MOD) % MOD;
		}
		c[gcd] = int((c[gcd] + 1LL * sum_a * sum_b) % MOD);
	}
	return c;
}
