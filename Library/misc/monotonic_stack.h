#pragma once
//library checker tests: https://judge.yosupo.jp/problem/cartesian_tree
//left[i] is the closest smaller index where arr is less.
//Formally: for every index j with left[i] < j < i: arr[j] >= arr[i]
//and
//arr[left[i]] < arr[i] if left[i] != -1
//O(n)
//
//example usage:
//	vector<int> left = monotonic_stack(arr);
//	reverse(arr.begin(), arr.end());
//	vector<int> right = monotonic_stack(arr);
//	reverse(arr.begin(), arr.end());
//	for (int i = 0; i < n; i++) {
//		int L = left[i] + 1, R = n - 2 - right[n - 1 - i];
//		//arr[i] is the min of inclusive range [L, R], with 0 <= L <= i <= R < n
//	}
vector<int> monotonic_stack(const vector<int>& arr) {
	int n = arr.size();
	vector<int> left(n);
	for (int i = 0; i < n; i++) {
		int& j = left[i] = i - 1;
		while (j >= 0 && arr[j] >= arr[i]) j = left[j];
	}
	return left;
}
