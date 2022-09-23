#pragma once
//returns number of distinct subsequences
//the empty subsequence is counted
int num_subsequences(const vector<int>& arr, int mod) {
	int n = ssize(arr);
	vector<int> dp(n + 1, 1);
	map<int, int> last;
	for (int i = 0; i < n; i++) {
		int& curr = dp[i + 1] = 2 * dp[i];
		if (curr >= mod) curr -= mod;
		auto it = last.find(arr[i]);
		if (it != last.end()) {
			curr -= dp[it->second];
			if (curr < 0) curr += mod;
			it->second = i;
		} else last[arr[i]] = i;
	}
	return dp[n];
}
