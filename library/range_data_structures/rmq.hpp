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
template <typename T> struct RMQ {
	vector<vector<T>> dp;
	function<T(const T&, const T&)> op;
	RMQ(const vector<T>& arr, const function<T(const T&, const T&)>& a_op) : dp(1, arr), op(a_op) {
		for (int pw = 1, k = 1; 2 * pw <= ssize(arr); pw *= 2, k++) {
			dp.emplace_back(ssize(arr) - 2 * pw + 1);
			for (int j = 0; j < ssize(dp.back()); j++)
				dp[k][j] = op(dp[k - 1][j], dp[k - 1][j + pw]);
		}
	}
	//inclusive-exclusive range [le, ri)
	T query(int le, int ri) const {
		assert(0 <= le && le < ri && ri <= ssize(dp[0]));
		int lg = __lg(ri - le);
		return op(dp[lg][le], dp[lg][ri - (1 << lg)]);
	}
};
