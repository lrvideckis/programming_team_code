#pragma once
//usages:
//	vector<int> le = monotonic_stack<int>(arr, less()); //(or replace `less` with: less_equal, greater, greater_equal
//	vector<int> le = monotonic_stack<int>(arr, [&](int x, int y) {return x < y;});
//
//returns array `le` where `le[i]` = max index such that:
//	`le[i]` < i && !op(arr[le[i]], arr[i])
//or -1 if no index exists
//O(n)
template<class T> vector<int> monotonic_stack(const vector<T>& arr, const function<bool(const T&, const T&)>& op) {
	vector<int> le(ssize(arr));
	for (int i = 0; i < ssize(arr); i++) {
		le[i] = i - 1;
		while (le[i] >= 0 && op(arr[le[i]], arr[i])) le[i] = le[le[i]];
	}
	return le;
}
