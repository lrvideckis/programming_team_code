/** @file */
#pragma once
/**
 * @code{.cpp}
 *     vector<long long> arr;
 *     vector<int> le = monotonic_stack<long long>(arr, less()); //less, less_equal, greater, greater_equal
 *     vector<int> le = monotonic_stack<long long>(arr, [&](long long x, long long y) {return x < y;});
 * @endcode
 * @param arr array
 * @param less any transitive compare operator
 * @returns array le where le[i] = max integer such that: le[i] < i and
 * less(arr[le[i]], arr[i]). If no integer exists, le[i] = -1
 * @time O(n)
 * @memory O(n)
 */
template <typename T> vector<int> monotonic_stack(const vector<T>& arr, const function<bool(const T&, const T&)>& less) {
	vector<int> le(ssize(arr));
	for (int i = 0; i < ssize(arr); i++) {
		le[i] = i - 1;
		while (le[i] >= 0 && !less(arr[le[i]], arr[i])) le[i] = le[le[i]];
	}
	return le;
}
