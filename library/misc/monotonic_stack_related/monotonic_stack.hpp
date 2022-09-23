#pragma once
//usages:
//	vector<int> left = monotonic_stack<int>(arr, less()); //(or replace `less` with: less_equal, greater, greater_equal
//	vector<int> left = monotonic_stack<int>(arr, [&](int x, int y) {return x < y;});
//
//returns array `left` where `left[i]` = max index such that:
//	`left[i]` < i && !op(arr[left[i]], arr[i])
//or -1 if no index exists
//O(n)
template<class T> vector<int> monotonic_stack(const vector<T>& arr, const function<bool(const T&, const T&)>& op) {
	vector<int> left(ssize(arr));
	for (int i = 0; i < ssize(arr); i++) {
		int& j = left[i] = i - 1;
		while (j >= 0 && op(arr[j], arr[i])) j = left[j];
	}
	return left;
}
