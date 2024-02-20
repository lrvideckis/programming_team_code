const int mod = 998'244'353;
/**
 * @see https://oeis.org/A000041
 * @param n an integer
 * @returns array p where p[i] = number of partitions of i numbers
 * @time O(n sqrt n) note there does exist a O(n log n) solution as well
 * @space O(n) for `dp` vector
 */
vector<int64_t> partitions(int n) {
	vector<int64_t> dp(n, 1);
	for (int i = 1; i < n; i++) {
		auto sum = 0LL;
		for (int j = 1, pent = 1, sign = 1; pent <= i; j++, pent += 3 * j - 2, sign = -sign) {
			if (pent + j <= i) sum += dp[i - pent - j] * sign + mod;
			sum += dp[i - pent] * sign + mod;
		}
		dp[i] = sum % mod;
	}
	return dp;
}
