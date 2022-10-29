#pragma once
//sources: https://codeforces.com/blog/entry/87940, https://github.com/sgtlaugh/algovault/blob/ master/code_library/disjoint_sparse_table.cpp
//Disjoint RMQ is like normal RMQ except these ranges don't overlap. So
//now, you can do a rmq with +, although it's overkill as you can do prefix sums
//instead. Also note seg trees can do everything this can do. It is useful for:
//	- min and # of mins.
//	- product under composite mod
//	- 2-by-2 matrix multiply
//usage for min and # of mins:
//	vector<pair<long long, int>> arr; //initialize arr[i].second = 1
//	...
//	disjoint_rmq<pair<long long, int>> rmq(arr, {LLONG_MAX, 0}, [&](auto x, auto y) {
//		if (x.first == y.first)
//			return make_pair(x.first, x.second + y.second);
//		return min(x, y);
//	});
template <typename T> struct disjoint_rmq {
	const int N;
	vector<vector<T>> dp;
	function<T(const T&, const T&)> op; // any associative operation
	disjoint_rmq(const vector<T>& arr, const T& identity, const function<T(const T&, const T&)>& a_op) : N(ssize(arr)), dp(__lg(N) + 1, vector<T>(N + 1, identity)), op(a_op) {
		for (int lg = 0; lg < ssize(dp); lg++) {
			int len = (1 << lg);
			for (int center = len; center < N + len; center += 2 * len) {
				for (int i = center + 1; i <= min(N, center + len); i++)
					dp[lg][i] = op(dp[lg][i - 1], arr[i - 1]);
				for (int i = min(N, center) - 1; i >= center - len; i--)
					dp[lg][i] = op(arr[i], dp[lg][i + 1]);
			}
		}
	}
	//range [le, ri)
	T query(int le, int ri) const {
		assert(0 <= le && le < ri && ri <= N);
		int lg = __lg(le ^ ri);
		return op(dp[lg][le], dp[lg][ri]);
	}
};
