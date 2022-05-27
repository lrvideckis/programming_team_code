#pragma once
//library checker tests: https://judge.yosupo.jp/problem/staticrmq, https://judge.yosupo.jp/problem/zalgorithm, https://judge.yosupo.jp/problem/enumerate_palindromes

//usage:
//	vector<long long> arr;
//	...
//	sparseTable<long long> st(arr, [](auto x, auto y) { return min(x,y); });
//
//to also get index of min element, do:
//	sparseTable<pair<long long,int>> st(arr, [](auto x, auto y) { return min(x,y); });
//and initialize `.second`'s to index. If there are multiple indexes of min element,
//it'll return the smallest (left-most) one
template <class T>
struct sparseTable {
	vector<vector<T>> dp;
	function<T(const T&, const T&)> func;
	sparseTable(const vector<T>& arr, const function<T(const T&, const T&)>& _func) : dp(1, arr), func(_func) {
		int n = arr.size();
		for (int pw = 1, k = 1; pw * 2 <= n; pw *= 2, k++) {
			dp.emplace_back(n - pw * 2 + 1);
			for (int j = 0; j < (int)dp[k].size(); j++)
				dp[k][j] = func(dp[k - 1][j], dp[k - 1][j + pw]);
		}
	}
	//inclusive range [l, r]
	T query(int l, int r) const {
		int lg = 31 - __builtin_clz(r - l + 1);
		return func(dp[lg][l], dp[lg][r - (1 << lg) + 1]);
	}
};
