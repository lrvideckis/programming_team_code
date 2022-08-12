#pragma once
//source: https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/RMQ.h
//usage:
//	vector<long long> arr;
//	...
//	RMQ<long long> rmq(arr, [&](auto x, auto y) { return min(x,y); });
//
//to also get index of min element, do:
//	RMQ<pair<T, int>> rmq(arr, [&](auto x, auto y) { return min(x,y); });
//and initialize arr[i].second = i (0<=i<n)
//If there are multiple indexes of min element, it'll return the smallest
//(left-most) one
//mnemonic: Range Min/Max Query
//NOLINTNEXTLINE(readability-identifier-naming)
template <class T> struct RMQ {
	vector<vector<T>> dp;
	function<T(const T&, const T&)> func;
	RMQ(const vector<T>& arr, const function<T(const T&, const T&)>& a_func) : dp(1, arr), func(a_func) {
		for (int pw = 1, k = 1, n = arr.size(); 2 * pw <= n; pw *= 2, k++) {
			dp.emplace_back(n - 2 * pw + 1);
			for (int j = 0; j < n - 2 * pw + 1; j++)
				dp[k][j] = func(dp[k - 1][j], dp[k - 1][j + pw]);
		}
	}
	//inclusive-exclusive range [l, r)
	T query(int l, int r) const {
		assert(0 <= l && l < r && r <= (int)dp[0].size());
		int lg = __lg(r - l);
		return func(dp[lg][l], dp[lg][r - (1 << lg)]);
	}
};
