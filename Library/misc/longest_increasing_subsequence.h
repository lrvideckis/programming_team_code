#pragma once

// status: stress tested, and tested on https://open.kattis.com/problems/longincsubseq

//returns array of indexes representing the longest *strictly* increasing subsequence
//for non-decreasing: pass in a vector<pair<T, int>> where second is 0, 1, ..., n-1
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
	}
	vector<int> res(dp.size());
	for (int i = dp.back(), j = dp.size(); i != -1; i = prev[i])
		res[--j] = i;
	return res;
}

//returns length of longest *strictly* increasing subsequence
//alternatively, there's this https://codeforces.com/blog/entry/13225
template<class T>
int lisSize(const vector<T>& arr) {
	vector<int> dp;
	for (int val : arr) {
		auto it = lower_bound(dp.begin(), dp.end(), val);
		if (it == dp.end()) dp.push_back(val);
		else *it = val;
		//here, `dp.size()` = length of LIS of prefix of `arr` so far
	}
	return dp.size();
}
