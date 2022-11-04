#pragma once
/**
 * @brief Disjoint RMQ is like normal RMQ except these ranges never overlap. It
 *     is useful for:
 *     - min and # of mins.
 *     - product under composite mod
 *     - 2-by-2 matrix multiply
 * @code{.cpp}
 *     //usage for min and # of mins:
 *     vector<pair<long long, int>> arr; //initialize arr[i].second = 1
 *     disjoint_rmq<pair<long long, int>> rmq(arr, {LLONG_MAX, 0}, [&](auto x, auto y) {
 *         if (x.first == y.first) return make_pair(x.first, x.second + y.second);
 *         return min(x, y);
 *     });
 * @endcode
 * @see https://codeforces.com/blog/entry/87940,
 *     https://github.com/sgtlaugh/algovault/blob/
 *     master/code_library/disjoint_sparse_table.cpp
 */
template <typename T> struct disjoint_rmq {
	const int N;
	vector<vector<T>> dp;
	function<T(const T&, const T&)> op; // any associative operation
	/**
	 * @time O(n log n)
	 * @memory O(n log n)
	 */
	disjoint_rmq(const vector<T>& arr, const T& identity, const function<T(const T&, const T&)>& a_op) : N(ssize(arr)), op(a_op) {
		for (int i = 0, len = 1; len <= N; i++, len *= 2) {
			dp.emplace_back(N + 1, identity);
			for (int center = len; center < N + len; center += 2 * len) {
				for (int j = center + 1; j <= min(N, center + len); j++)
					dp[i][j] = op(dp[i][j - 1], arr[j - 1]);
				for (int j = min(N, center) - 1; j >= center - len; j--)
					dp[i][j] = op(arr[j], dp[i][j + 1]);
			}
		}
	}
	/**
	 * @note range [le, ri)
	 * @time O(1)
	 */
	T query(int le, int ri) const {
		assert(0 <= le && le < ri && ri <= N);
		int lg = __lg(le ^ ri);
		return op(dp[lg][le], dp[lg][ri]);
	}
};
