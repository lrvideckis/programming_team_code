#pragma once
//calculates array `left` with:
//for every index j with left[i] < j < i: arr[j] > arr[i]
//and
//arr[left[i]] <= arr[i] if left[i] != -1
//
//trick: pass in vector<pair<T/*value*/, int/*index*/>> with arr[i].second = i (0<=i<n) to simulate arr[j] >= arr[i]
//
//O(n)
template<class T> vector<int> monotonic_stack(const vector<T>& arr) {
	int n = ssize(arr);
	vector<int> left(n);
	for (int i = 0; i < n; i++) {
		int& j = left[i] = i - 1;
		while (j >= 0 && arr[j] > arr[i]) j = left[j];
	}
	return left;
}
