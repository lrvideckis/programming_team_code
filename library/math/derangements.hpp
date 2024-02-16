/**
 * @see https://oeis.org/A000166
 * @param n size
 * @param mod an integer
 * @return number of permutations p such that p[i] != i
 * @time O(n)
 * @space O(n) for `dp` vector
 */
vector<long long> derangements(int n, int mod) {
	vector dp(n, 0LL);
	dp[0] = 1;
	for (int i = 2; i < n; i++)
		dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2]) % mod;
	return dp;
}
