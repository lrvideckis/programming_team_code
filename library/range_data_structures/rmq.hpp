#pragma once
//source: https://github.com/kth-competitive-programming/
//	kactl/blob/main/content/data-structures/RMQ.h
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
	function<T(const T&, const T&)> op;
	//inclusive-exclusive range [l, r)
	RMQ(const vector<T>& arr, const function<T(const T&, const T&)>& a_op) : dp(1, arr), op(a_op) {
		for (int pw = 1, k = 1, n = arr.size(); 2 * pw <= n; pw *= 2, k++) {
			dp.emplace_back(n - 2 * pw + 1);
			for (int j = 0; j < n - 2 * pw + 1; j++)
				dp[k][j] = op(dp[k - 1][j], dp[k - 1][j + pw]);
		}
	}
	T query(int l, int r) const {
		assert(0 <= l && l < r && r <= (int)dp[0].size());
		int LG = __lg(r - l);
		return op(dp[LG][l], dp[LG][r - (1 << LG)]);
	}
};
