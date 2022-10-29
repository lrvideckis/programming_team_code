#pragma once
#include "suffix_array.hpp"
#include "longest_common_prefix.hpp"
#include "../range_data_structures/rmq.hpp"
//computes suffix array, lcp array, and then sparse table over lcp array
//O(n log n)
template <typename T> struct lcp_query {
	const int N;
	vector<int> sa, inv_sa, lcp;
	RMQ<int> rmq;
	lcp_query(const T& s, int max_val) : N(ssize(s)), sa(suffix_array(s, max_val)), inv_sa(N), lcp(calc_lcp(s, sa)), rmq(lcp, [](int i, int j) -> int {return min(i, j);}) {
		for (int i = 0; i < N; i++)
			inv_sa[sa[i]] = i;
	}
	//length of longest common prefix of suffixes s[idx1 ... N), s[idx2 ... N), 0-based indexing
	//
	//You can check if two substrings s[l1..r1), s[l2..r2) are equal in O(1) by:
	//r1-l1 == r2-l2 && longest_common_prefix(l1, l2) >= r1-l1
	int get_lcp(int idx1, int idx2) const {
		if (idx1 == idx2)
			return N - idx1;
		auto [le, ri] = minmax(inv_sa[idx1], inv_sa[idx2]);
		return rmq.query(le, ri);
	}
	//returns 1 if suffix s[idx1 ... N) < s[idx2 ... N)
	//(so 0 if idx1 == idx2)
	bool less(int idx1, int idx2) const {
		return inv_sa[idx1] < inv_sa[idx2];
	}
};
