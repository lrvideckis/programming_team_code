#pragma once
#include "monotonic_stack.h"

vector<int> cartesian_tree(const vector<int>& arr) {
	int n = arr.size();
	auto rv /*reverse*/ = [&](int i) -> int {
		return n - 1 - i;
	};
	vector<int> left = monotonic_stack<int>(arr, greater());
	vector<int> right = monotonic_stack<int>(vector<int>(arr.rbegin(), arr.rend()), greater());
	vector<int> par(n);
	for (int i = 0; i < n; i++) {
		int l = left[i], r = rv(right[rv(i)]);
		if (l >= 0 && r < n) par[i] = arr[l] > arr[r] ? l : r;
		else if (l >= 0 || r < n) par[i] = l >= 0 ? l : r;
		else par[i] = i;
	}
	return par;
}
