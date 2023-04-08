/** @file */
#pragma once
/**
 * @code{.cpp}
 *     vector<int> le = monotonic_stack<int>(arr, less());
 *     vector<int> le = monotonic_stack<int>(arr, [&](int x, int y) {return x < y;});
 * @endcode
 * @param arr array
 * @param cmp one of less, less_equal, greater, greater_equal
 * @returns array `le` where `le[i]` = max integer such that: `le[i]` < i and
 * !cmp(arr[le[i]], arr[i]). Returns -1 if no number exists.
 * @time O(n)
 * @memory O(n)
 */
template <typename T> vector<int> monotonic_stack(const vector<T>& arr, const function<bool(const T&, const T&)>& cmp) {
	vector<int> le(ssize(arr));
	for (int i = 0; i < ssize(arr); i++) {
		le[i] = i - 1;
		while (le[i] >= 0 && cmp(arr[le[i]], arr[i])) le[i] = le[le[i]];
	}
	return le;
}
