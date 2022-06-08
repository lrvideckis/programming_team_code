#pragma once
//library checker tests: https://judge.yosupo.jp/problem/cartesian_tree
//calculates array `left` with:
//for every index j with left[i] < j < i: arr[j] > arr[i]
//and
//arr[left[i]] <= arr[i] if left[i] != -1
//
//O(n)
vector<int> monotonic_stack(const vector<int>& arr) {
	int n = arr.size();
	vector<int> left(n);
	for (int i = 0; i < n; i++) {
		int& j = left[i] = i - 1;
		while (j >= 0 && arr[j] > arr[i]) j = left[j];
	}
	return left;
}
