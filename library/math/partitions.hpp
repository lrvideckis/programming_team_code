/** @file */
#pragma once
/**
 * @see https://oeis.org/A000041
 * @param n an integer
 * @param mod an integer
 * @returns array p where p[i] = number of partitions of i numbers
 * @time O(n sqrt n) note there does exist a O(n log n) solution as well
 */
vector<long long> partitions(int n, long long mod) {
	vector<long long> dp(n, 1);
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
