#pragma once
#include "../../ac-library/atcoder/string.hpp"
#include "../range_data_structures/rmq.hpp"
//computes suffix array, lcp array, and then sparse table over lcp array
//O(n log n)
template <typename T> struct lcp_query {
	vector<int> sa, lcp, inv_sa;
	RMQ<int> rmq;
	lcp_query(const T& s) : sa(atcoder::suffix_array(s)), lcp(atcoder::lcp_array(s, sa)), inv_sa(ssize(s)), rmq(lcp, [](int x, int y) {
		return min(x, y);
	}) {
		for (int i = 0; i < ssize(sa); i++)
			inv_sa[sa[i]] = i;
	}
	//length of longest common prefix of suffixes s[idx1 ... n), s[idx2 ... n), 0-based indexing
	//
	//You can check if two substrings s[l1..r1), s[l2..r2) are equal in O(1) by:
	//r1-l1 == r2-l2 && longest_common_prefix(l1, l2) >= r1-l1
	int get_lcp(int idx1, int idx2) const {
		if (idx1 == idx2)
			return ssize(sa) - idx1;
		auto [le, ri] = minmax(inv_sa[idx1], inv_sa[idx2]);
		return rmq.query(le, ri);
	}
	//returns 1 if suffix s[idx1 ... n) < s[idx2 ... n)
	//(so 0 if idx1 == idx2)
	bool less(int idx1, int idx2) const {
		return inv_sa[idx1] < inv_sa[idx2];
	}
};
