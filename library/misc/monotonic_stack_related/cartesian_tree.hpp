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
		int le = left[i], ri = rv(right[rv(i)]);
		if (le >= 0 && ri < n)
			par[i] = arr[le] > arr[ri] ? le : ri;
		else if (le >= 0)
			par[i] = le;
		else if (ri < n)
			par[i] = ri;
		else
			par[i] = i;
	}
	return par;
}
