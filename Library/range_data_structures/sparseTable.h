#pragma once

//usage:
//	vector<long long> arr;
//	...
//	sparseTable<long long> st(arr, [](auto x, auto y) { return min(x,y); });
//
//to also get index of min element, do:
//	sparseTable<pair<long long,int>> st(arr, [](auto x, auto y) { return min(x,y); });
//and initialize second to index. If there are multiple indexes of min element,
//it'll return the smallest (left-most) one
//
//status: tested on random inputs, also on https://judge.yosupo.jp/problem/staticrmq
template <class T>
struct sparseTable {
	vector<int> log2;
	vector<vector<T>> dp;
	function<T(const T&, const T&)> func;
	sparseTable(const vector<T>& arr, const function<T(const T&, const T&)>& _func) : func(_func) {
		const int n = arr.size();
		log2.resize(n + 1, -1);
		for (int i = 1; i <= n; ++i) log2[i] = 1 + log2[i / 2];
		dp.resize(log2[n] + 1, arr);
		for (int i = 1; i <= log2[n]; ++i) {
			for (int j = 0; j + (1 << i) - 1 < n; ++j)
				dp[i][j] = func(dp[i - 1][j], dp[i - 1][j + (1 << (i - 1))]);
		}
	}
	//returns func of arr[l], arr[l+1], ..., arr[r]
	T query(int l, int r) const {
		const int x = log2[r - l + 1];
		return func(dp[x][l], dp[x][r - (1 << x) + 1]);
	}
};
