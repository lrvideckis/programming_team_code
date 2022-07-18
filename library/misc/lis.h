#pragma once
//returns array of indexes representing the longest *strictly* increasing subsequence
//for non-decreasing: pass in a vector<pair<T, int>> with arr[i].second = i (0<=i<n)
//alternatively, there's this https://codeforces.com/blog/entry/13225
//mnemonic: Longest Increasing Subsequence
//NOLINTNEXTLINE(readability-identifier-naming)
template<class T> vector<int> LIS(const vector<T>& arr) {
	if (arr.empty()) return {};
	vector<int> dp{0}/*array of indexes into `arr`*/, prev(arr.size(), -1);
	for (int i = 1; i < (int)arr.size(); i++) {
		auto it = lower_bound(dp.begin(), dp.end(), i, [&](int x, int y) -> bool {
			return arr[x] < arr[y];
		});
		if (it == dp.end()) {
			prev[i] = dp.back();
			dp.push_back(i);
		} else {
			prev[i] = it == dp.begin() ? -1 : *(it - 1);
			*it = i;
		}
		//here, dp.size() = length of LIS of prefix of arr ending at index i
	}
	vector<int> res(dp.size());
	for (int i = dp.back(), j = dp.size(); i != -1; i = prev[i])
		res[--j] = i;
	return res;
}
