#pragma once

// status: tested on https://open.kattis.com/problems/longincsubseq

//returns array of indexes representing the longest *strictly* increasing subsequence
//for non-decreasing: pass in a vector<pair<T, int>> where second is 0, 1, ..., n-1
template<class T>
vector<int> lis(const vector<T>& arr) {
	int n = arr.size();
	vector<int> dp/*array of indexes into `arr`*/, prev(n);
	for (int i = 0; i < n; i++) {
		auto it = lower_bound(dp.begin(), dp.end(), i, [&](int x, int y) -> bool {
			return arr[x] < arr[y];
		});
		if (it == dp.end()) {
			prev[i] = dp.empty() ? -1 : dp.back();
			dp.push_back(i);
		} else {
			prev[i] = it == dp.begin() ? -1 : *(it - 1);
			*it = i;
		}
	}
	vector<int> res(dp.size());
	int j = dp.size();
	for (int i = dp.back(); i != -1; i = prev[i])
		res[--j] = i;
	return res;
}
