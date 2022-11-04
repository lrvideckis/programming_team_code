#pragma once
/**
 * @see https://oeis.org/A000166
 * @time O(n)
 */
vector<long long> derangements(int n, long long mod) {
	vector<long long> dp(n, 0);
	dp[0] = 1;
	for (int i = 2; i < n; i++)
		dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2]) % mod;
	return dp;
}
