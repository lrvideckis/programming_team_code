#pragma once
#include "monotonic_stack.hpp"
/**
 * Min cartesian tree - root stores min.
 * @time O(n)
 * @memory O(n)
 */
vector<int> cartesian_tree(const vector<int>& arr) {
	int n = ssize(arr);
	vector<int> left = monotonic_stack<int>(arr, greater());
	vector<int> right = monotonic_stack<int>(vector<int>(arr.rbegin(), arr.rend()), greater());
	vector<int> par(n);
	transform(left.begin(), left.end(), right.rbegin(), par.begin(), [&](int le, int ri) {
		ri = n - 1 - ri;
		if (le >= 0 && ri < n) return arr[le] > arr[ri] ? le : ri;
		if (le >= 0) return le;
		if (ri < n) return ri;
		return -1; //root
	});
	return par;
}
