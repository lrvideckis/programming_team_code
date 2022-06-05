#pragma once
//library checker tests: https://judge.yosupo.jp/problem/cartesian_tree
//leftLower[i] is the closest smaller index where arr is less.
//Formally: for every index j with leftLower[i] < j < i: arr[j] >= arr[i]
//and
//arr[leftLower[i]] < arr[i] if leftLower[i] != -1
//
//example usage:
//	vector<int> leftLower = monotonic_stack(arr);
//	reverse(arr.begin(), arr.end());
//	vector<int> rightLower = monotonic_stack(arr);
//	reverse(arr.begin(), arr.end());
//	for (int i = 0; i < n; i++) {
//		int L = leftLower[i] + 1, R = n - 2 - rightLower[n - 1 - i];
//		//arr[i] is the min of inclusive range [L, R], with 0 <= L <= i <= R < n
//	}
vector<int> monotonic_stack(const vector<int>& arr) {
	int n = arr.size();
	stack<int> st;
	vector<int> leftLower(n, -1);
	for (int i = 0; i < n; i++) {
		while (!st.empty() && arr[st.top()] >= arr[i]) st.pop();
		if (!st.empty()) leftLower[i] = st.top();
		st.push(i);
	}
	return leftLower;
}
