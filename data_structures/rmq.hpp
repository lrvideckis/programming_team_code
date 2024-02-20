/**
 * @code{.cpp}
       vector<int64_t> a;
       RMQ rmq(a, ranges::min); // -std=c++20
       RMQ rmq(a, [&](auto& x, auto& y) { return min(x, y); });
 * @endcode
 */
template <class T, class F> struct RMQ {
	vector<vector<T>> dp;
	F op;
	RMQ() {}
	/**
	 * @param a static array
	 * @param a_op any associative, communative, idempotent operation
	 * @time O(n log n)
	 * @space O(n log n) for `dp` vector
	 */
	RMQ(const vector<T>& a, F a_op) : dp(1, a), op(a_op) {
		for (int i = 0; (2 << i) <= ssize(a); i++) {
			dp.emplace_back(ssize(a) - (2 << i) + 1);
			transform(begin(dp[i]), end(dp[i]) - (1 << i), begin(dp[i]) + (1 << i), begin(dp[i + 1]), op);
		}
	}
	/**
	 * @param le,ri defines range [le, ri)
	 * @returns a[le] op a[le + 1] op ... op a[ri - 1]
	 * @time O(1)
	 * @space O(1)
	 */
	inline T query(int le, int ri) {
		assert(0 <= le && le < ri && ri <= ssize(dp[0]));
		int lg = __lg(ri - le);
		return op(dp[lg][le], dp[lg][ri - (1 << lg)]);
	}
};
