#pragma once
//library checker tests: https://judge.yosupo.jp/problem/cartesian_tree
//leftLower[i] is the closest smaller index where arr is less.
//Formally: for every index j with leftLower[i] < j < i: arr[j] >= arr[i]
//and
//arr[leftLower[i]] < arr[i] if leftLower[i] != -1
//O(n)
//
//example usage:
//	vector<int> leftLower = monotonic_stack(arr);
//	reverse(arr.begin(), arr.end());
//	vector<int> rightLower = monotonic_stack(arr);
//	reverse(arr.begin(), arr.end());
//	for (int i = 0; i < n; i++) {
//		int L = leftLower[i] + 1, R = n - 2 - rightLower[n - 1 - i];
//		//arr[i] is the min of inclusive range [L, R], with 0 <= L <= i <= R < n
//	}
vector<int> monotonic_stack(const vector<int>& arr) {
	int n = arr.size();
	vector<int> leftLower(n);
	for (int i = 0; i < n; i++) {
		int j = i - 1;
		while (j >= 0 && arr[j] >= arr[i]) j = leftLower[j];
		leftLower[i] = j;
	}
	return leftLower;
}
