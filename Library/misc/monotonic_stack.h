#pragma once
//library checker tests: https://judge.yosupo.jp/problem/cartesian_tree

//leftLower[i] is the closest index where arr is less.
//Formally: for every index j with leftLower[i] < j < i: arr[j] >= arr[i]
//and
//arr[leftLower[i]] < arr[i] if leftLower[i] != -1
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
