#pragma once
//source: https://codeforces.com/blog/entry/87940
template <typename T> struct disjoint_rmq {
	const int N;
	vector<vector<T>> dp;
	function<T(const T&, const T&)> op;
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
