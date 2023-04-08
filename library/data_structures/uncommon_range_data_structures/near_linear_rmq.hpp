/** @file */
#pragma once
//https://codeforces.com/blog/entry/78931
//https://codeforces.com/blog/entry/92310
//https://github.com/okwedook/olymp/blob/master/code/data-structures/LinearMinTable.hpp
//TODO: have least_common_ancestor.hpp depend on this
//
//memory: theoretically O(nlogn / log(log(n))), practically: 3 vector<unsigned long long>'s of size n
template <typename T> struct name_todo {
	using ull = unsigned long long;
	const int N;
	vector<T> arr;
	vector<vector<ull>> mask;
	function<bool(const T&, const T&)> less; //any transitive compare operator
	int min_ind(int l, int r) const {
		return less(arr[l], arr[r]) ? l : r;
	}
	name_todo(const vector<T>& a_arr, function<bool(const T&, const T&)> a_cmp) : N(ssize(a_arr)), mask(1, arr), less(a_cmp) {
		iota(mask[0].begin(), mask[0].end(), 0);
		for(int lg = 6, b = 64;; lg += 6, b *= 64) {

			ull curr_mask = 0;
			for(int i = 0; i < ssize(mask.back()); i++) {
				while(curr_mask && less(arr[
			}

			if(ssize(mask.back()) <= 2 * 64) break;

			int sz_new_level = (n + 64 - 1) >> 6;
		}
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
