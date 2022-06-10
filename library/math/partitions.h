#pragma once
//library checker tests: https://judge.yosupo.jp/problem/partition_function
//https://oeis.org/A000041
//O(n sqrt n) time, but small-ish constant factor (there does exist a O(n log n) solution too)
vector<int> partitions(int n/*size of dp array*/, int mod) {
	vector<int> dp(n, 1);
	for (int i = 1; i < n; i++) {
		long long sum = 0;
		for (int j = 1, pent = 1, sign = 1; pent <= i; j++, pent += 3 * j - 2, sign = -sign) {
			if (pent + j <= i) sum += dp[i - pent - j] * sign + mod;
			sum += dp[i - pent] * sign + mod;
		}
		dp[i] = sum % mod;
	}
	return dp;
}
