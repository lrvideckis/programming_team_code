#pragma once
#include "monotonic_stack.h"
long long max_rect_histogram(const vector<int>& arr) {
	int n = arr.size();
	auto rv /*reverse*/ = [&](int j) -> int {
		return n - 1 - j;
	};
	//vector<int> left = monotonic_stack<int>(arr, greater_equal());
	vector<int> left = monotonic_stack<int>(arr, greater_equal());
	vector<int> right = monotonic_stack<int>(vector<int>(arr.rbegin(), arr.rend()), greater_equal());
	long long max_area = 0;
	for (int i = 0; i < n; i++) {
		int l = left[i], r = rv(right[rv(i)]);//arr[i] is the max of range (l, r)
		max_area = max(max_area, 1LL * arr[i] * (r - l - 1));
	}
	return max_area;
}
