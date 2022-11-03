#pragma once
/**
 * @brief Returns array `le` where `le[i]` = max number such that: `le[i]` < i
 *     and !op(arr[le[i]], arr[i]). Returns -1 if no number exists.
 * @code{.cpp}
 *     vector<int> le = monotonic_stack<int>(arr, less()); //(or replace `less` with: less_equal, greater, greater_equal
 *     vector<int> le = monotonic_stack<int>(arr, [&](int x, int y) {return x < y;});
 * @endcode
 * @time O(n)
 * @memory O(n)
 */
template <typename T> vector<int> monotonic_stack(const vector<T>& arr, const function<bool(const T&, const T&)>& op) {
	vector<int> le(ssize(arr));
	for (int i = 0; i < ssize(arr); i++) {
		le[i] = i - 1;
		while (le[i] >= 0 && op(arr[le[i]], arr[i]))
			le[i] = le[le[i]];
	}
	return le;
}
