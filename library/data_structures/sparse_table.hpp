/** @file */
#pragma once
/**
 * @code{.cpp}
 *     vector<long long> arr;
 *     RMQ<long long> rmq(arr, [&](auto x, auto y) { return min(x, y); });
 *
 *     //To get index of min element:
 *     vector<pair<long long, int>> arr; //initialize arr[i].second = i
 *     RMQ<pair<long long, int>> rmq(arr, [&](auto x, auto y) { return min(x, y); });
 * @endcode
 */
//NOLINTNEXTLINE(readability-identifier-naming)
template <typename T> struct RMQ {
	vector<vector<T>> dp; /**< dp[i][j] = op of range [j, j + 2^i) */
	function<T(const T&, const T&)> op; /**< usually min,max,and,or,gcd */
	/**
	 * @param arr static array
	 * @param a_op any associative, communative, idempotent operation
	 * @time O(n log n)
	 * @memory O(n log n)
	 */
	RMQ(const vector<T>& arr, const function<T(const T&, const T&)>& a_op) : dp(1, arr), op(a_op) {
		for (int i = 0; (2 << i) <= ssize(arr); i++) {
			dp.emplace_back(ssize(arr) - (2 << i) + 1);
			transform(dp[i].begin() + (1 << i), dp[i].end(), dp[i].begin(), dp[i + 1].begin(), op);
		}
	}
	/**
	 * @param le,ri defines range [le, ri)
	 * @returns op of range
	 * @time O(1) usually, or O(log MAX) if op is gcd
	 */
	T query(int le, int ri) const {
		assert(0 <= le && le < ri && ri <= ssize(dp[0]));
		int lg = __lg(ri - le);
		return op(dp[lg][le], dp[lg][ri - (1 << lg)]);
	}
};
