#pragma once
/**
 * Disjoint RMQ is like normal RMQ except these ranges never overlap. It is
 * useful for:
 * - min and # of mins.
 * - product under composite mod
 * - matrix multiply
 * - function composition
 * @code{.cpp}
 *     //usage for min and # of mins:
 *     vector<pair<long long, int>> arr; //initialize arr[i].second = 1
 *     disjoint_rmq<pair<long long, int>> rmq(arr, [&](auto x, auto y) {
 *         if (x.first == y.first) return make_pair(x.first, x.second + y.second);
 *         return min(x, y);
 *     });
 * @endcode
 * @see https://codeforces.com/blog/entry/87940
 */
template <typename T> struct disjoint_rmq {
	const int N;
	vector<vector<T>> dp;
	function<T(const T&, const T&)> op; // any associative operation
	/**
	 * @time O(n log n)
	 * @memory O(n log n)
	 */
	disjoint_rmq(const vector<T>& arr, const function<T(const T&, const T&)>& a_op) : N(ssize(arr)), op(a_op) {
		for (int i = 0; (1 << i) <= N; i++) {
			dp.emplace_back(N);
			for (int le = 0; le < N; le += (2 << i)) {
				int mi = min(N, le + (1 << i)), ri = min(N, le + (2 << i));
				partial_sum(arr.rend() - mi, arr.rend() - le, dp[i].rend() - mi, [&](const T & x, const T & y) {return op(y, x);});
				partial_sum(arr.begin() + mi, arr.begin() + ri, dp[i].begin() + mi, op);
			}
		}
	}
	/**
	 * range [le, ri)
	 * @time O(1)
	 */
	T query(int le, int ri) const {
		assert(0 <= le && le < ri && ri <= N);
		if (ri - le == 1) return dp[0][le];
		int lg = __lg(le ^ (ri - 1));
		return op(dp[lg][le], dp[lg][ri - 1]);
	}
};
