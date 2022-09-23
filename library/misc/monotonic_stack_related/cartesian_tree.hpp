#pragma once
#include "monotonic_stack.hpp"
//min cartesian tree
vector<int> cartesian_tree(const vector<int>& arr) {
	int n = ssize(arr);
	auto rv /*reverse*/ = [&](int i) -> int {
		return n - 1 - i;
	};
	vector<int> left = monotonic_stack<int>(arr, greater());
	vector<int> right = monotonic_stack<int>(vector<int>(arr.rbegin(), arr.rend()), greater());
	vector<int> par(n);
	for (int i = 0; i < n; i++) {
		int l = left[i], r = rv(right[rv(i)]);
		if (l >= 0 && r < n) par[i] = arr[l] > arr[r] ? l : r;
		else if (l >= 0) par[i] = l;
		else if (r < n) par[i] = r;
		else par[i] = i;
	}
	return par;
}
