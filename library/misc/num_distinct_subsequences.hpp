/** @file */
#pragma once
/**
 * @param arr,mod self explanatory
 * @returns the number of distinct subsequences of `arr`. The empty subsequence
 * is counted.
 * @time O(n log n)
 * @memory O(n)
 */
int num_subsequences(const vector<int>& arr, int mod) {
    vector<int> dp(ssize(arr) + 1, 1);
    map<int, int> last;
    for (int i = 0; i < ssize(arr); i++) {
        int& curr = dp[i + 1] = 2 * dp[i];
        if (curr >= mod) curr -= mod;
        auto it = last.find(arr[i]);
        if (it != end(last)) {
            curr -= dp[it->second];
            if (curr < 0) curr += mod;
            it->second = i;
        } else last[arr[i]] = i;
    }
    return dp.back();
}
