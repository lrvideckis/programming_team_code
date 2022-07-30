#pragma once
#include "suffix_array.h"
#include "lcp.h"
#include "../range_data_structures/rmq.h"
//computes suffix array, lcp array, and then sparse table over lcp array
//O(n log n)
struct lcp_queries {
	lcp_queries(const string& s) : sa(sa_is(s, 255)), inv_sa(s.size()), lcp(LCP(s, sa)), st(lcp, [](int x, int y) {
		return min(x, y);
	}) {
		for (int i = 0; i < (int)s.size(); i++)
			inv_sa[sa[i]] = i;
	}
	//length of longest common prefix of suffixes s[idx1 ... n), s[idx2 ... n), 0-based indexing
	//
	//You can check if two substrings s[l1..r1), s[l2..r2) are equal in O(1) by:
	//r1-l1 == r2-l2 && longest_common_prefix(l1, l2) >= r1-l1
	int longest_common_prefix(int idx1, int idx2) const {
		if (idx1 == idx2) return (int)sa.size() - idx1;
		idx1 = inv_sa[idx1];
		idx2 = inv_sa[idx2];
		if (idx1 > idx2) swap(idx1, idx2);
		return st.query(idx1, idx2);
	}
	//returns 1 if suffix s[idx1 ... n) < s[idx2 ... n)
	//(so 0 if idx1 == idx2)
	bool less(int idx1, int idx2) const {
		return inv_sa[idx1] < inv_sa[idx2];
	}
	vector<int> sa, inv_sa, lcp;
	RMQ<int> st;
};
