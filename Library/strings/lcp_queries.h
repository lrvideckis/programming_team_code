#pragma once
//library checker tests: https://judge.yosupo.jp/problem/zalgorithm, https://judge.yosupo.jp/problem/enumerate_palindromes
#include "suffix_array.h"
#include "longest_common_prefix.h"
#include "../range_data_structures/sparseTable.h"
//computes suffix array, lcp array, and then sparse table over lcp array
//O(n log n)
struct lcp_queries {
	lcp_queries(const string& s) : sa(sa_is(s, 255)), inv_sa(s.size()), lcp(lcp_array(s, sa)), st(lcp, [](int x, int y) {
		return min(x, y);
	}) {
		for (int i = 0; i < (int)s.size(); i++)
			inv_sa[sa[i]] = i;
	}
	//length of longest common prefix of suffixes s[idx1 ... n-1], s[idx2 ... n-1], 0-based indexing
	//You can check if two substrings s[L1..R1], s[L2..R2] are equal in O(1) by:
	//
	//R2-L2 == R1-L1 && longest_common_prefix(L1, L2) >= R2-L2+1
	int longest_common_prefix(int idx1, int idx2) const {
		if (idx1 == idx2) return (int) sa.size() - idx1;
		idx1 = inv_sa[idx1];
		idx2 = inv_sa[idx2];
		if (idx1 > idx2) swap(idx1, idx2);
		return st.query(idx1, idx2 - 1);
	}
	//returns true if suffix s[idx1 ... n-1] < s[idx2 ... n-1]
	//(so false if idx1 == idx2)
	bool less(int idx1, int idx2) const {
		return inv_sa[idx1] < inv_sa[idx2];
	}
	vector<int> sa, inv_sa, lcp;
	sparseTable<int> st;
};
