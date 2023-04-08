/** @file */
#pragma once
//https://codeforces.com/blog/entry/78931
//https://codeforces.com/blog/entry/92310
//https://github.com/okwedook/olymp/blob/master/code/data-structures/LinearMinTable.hpp
//TODO: have least_common_ancestor.hpp depend on this, also, maybe suffix array query? hmm
//TODO: test on https://judge.yosupo.jp/problem/predecessor_problem
//
//memory: theoretically O(nlogn / log(log(n))), practically: 3 vector<unsigned long long>'s of size n
template <typename T> struct name_todo {
	using ull = unsigned long long;
	const int N;
	vector<vector<ull>> mask;
	function<bool(const T&, const T&)> cmp; //any transitive compare operator
	name_todo(const vector<T>& arr, const function<bool(const T&, const T&)>& a_cmp) : N(ssize(arr)), mask(1, a), cmp(a_cmp) {
		//TODO
	}
	int query_idx(int le, int ri) const {//time: theoretically O(log(n) / log(log(n))), practically 3 times complexity of normal RMQ query
		assert(0 <= le && le < ri && ri <= N);
		//TODO
		return -1;
	}
	void update(int idx, const T& val) {//time: theoretically O((log(n)^2) / log(log(n))), practically 3 * 64 array indexes
		//TODO
	}
};
