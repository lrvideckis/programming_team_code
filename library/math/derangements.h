#pragma once
//library checker tests: https://judge.yosupo.jp/problem/montmort_number_mod
//https://oeis.org/A000166
//
//for a permutation of size i:
//there are (i-1) places to move 0 to not be at index 0. Let's say we moved 0 to index j (j>0).
//If we move value j to index 0 (forming a cycle of length 2), then there are dp[i-2] derangements of the remaining i-2 elements
//else there are dp[i-1] derangements of the remaining i-1 elements (including j)
vector<int> derangements(int n/*size of dp array*/, int mod) {
	vector<int> dp(n, 0);
	dp[0] = 1;
	for (int i = 2; i < n; i++)
		dp[i] = 1LL * (i - 1) * (dp[i - 1] + dp[i - 2]) % mod;
	return dp;
}
