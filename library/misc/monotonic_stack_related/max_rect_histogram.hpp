#pragma once
#include "monotonic_stack.hpp"
/**
 * @time O(n)
 * @memory O(n)
 */
long long max_rect_histogram(const vector<int>& arr) {
	auto rv /*reverse*/ = [&](int i) -> int {
		return ssize(arr) - 1 - i;
	};
	vector<int> left = monotonic_stack<int>(arr, greater_equal());
	vector<int> right = monotonic_stack<int>(vector<int>(arr.rbegin(), arr.rend()), greater_equal());
	long long max_area = 0;
	for (int i = 0; i < ssize(arr); i++) {
		int le = left[i], ri = rv(right[rv(i)]);//arr[i] is the max of range (le, ri)
		max_area = max(max_area, 1LL * arr[i] * (ri - le - 1));
	}
	return max_area;
}
