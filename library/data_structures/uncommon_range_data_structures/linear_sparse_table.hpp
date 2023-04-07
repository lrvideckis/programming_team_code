/** @file */
#pragma once
//https://codeforces.com/blog/entry/78931
//https://codeforces.com/blog/entry/92310
//https://github.com/okwedook/olymp/blob/master/code/data-structures/LinearMinTable.hpp
template <typename T> struct linear_rmq {
	function<bool(const T&, const T&)> op;
	RMQ(const vector<T>& arr, const function<bool(const T&, const T&)>& a_op) : op(a_op) {
		//TODO
	}
	int query_idx(int le, int ri) const {//time: theoretically O(log(n) / log(log(n))), practically 3 times complexity of normal RMQ query
		assert(0 <= le && le < ri && ri <= ssize(dp[0]));
		//TODO
	}
	update(int idx, const T& val) {//time: theoretically O((log(n)^2) / log(log(n))), practically 3 * 64 array indexes
		//TODO
	}
};
