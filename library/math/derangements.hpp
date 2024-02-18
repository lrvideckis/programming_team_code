/** @file */
#pragma once
/**
 * @see https://oeis.org/A000166
 * @param n size
 * @param mod an integer
 * @return number of permutations p such that p[i] != i
 * @time O(n)
 * @space O(n) for `dp` vector
 */
vector<int64_t> derangements(int n, int mod) {
	vector<int64_t> dp(n);
	dp[0] = 1;
	for (int i = 2; i < n; i++)
		dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2]) % mod;
	return dp;
}
