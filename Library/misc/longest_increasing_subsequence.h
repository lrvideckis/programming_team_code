#pragma once
//library checker tests: https://judge.yosupo.jp/problem/static_range_lis_query

//returns array of indexes representing the longest *strictly* increasing subsequence
//for non-decreasing: pass in a vector<pair<T, int>> where second is 0, 1, ..., n-1
//alternatively, there's this https://codeforces.com/blog/entry/13225
template<class T>
vector<int> lis(const vector<T>& arr) {
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
