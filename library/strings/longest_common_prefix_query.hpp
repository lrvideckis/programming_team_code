#pragma once
#include "../../hackpack-cpp/content/strings/SuffixArray.h"
#include "../range_data_structures/rmq.hpp"
//computes suffix array, lcp array, and then sparse table over lcp array
//O(n log n)
struct lcp_query {
	SuffixArray info;
	RMQ<int> rmq;
	lcp_query(string& s) : info(SuffixArray(s)), rmq(vi(info.lcp.begin() + 1, info.lcp.end()), [](int i, int j) -> int {return min(i, j);}) {}
	//length of longest common prefix of suffixes s[idx1 ... N), s[idx2 ... N), 0-based indexing
	//
	//You can check if two substrings s[l1..r1), s[l2..r2) are equal in O(1) by:
	//r1-l1 == r2-l2 && longest_common_prefix(l1, l2) >= r1-l1
	int get_lcp(int idx1, int idx2) const {
		if (idx1 == idx2)
			return ssize(info.sa) - idx1;
		auto [le, ri] = minmax(info.rank[idx1], info.rank[idx2]);
		return rmq.query(le, ri);
	}
	//returns 1 if suffix s[idx1 ... N) < s[idx2 ... N)
	//(so 0 if idx1 == idx2)
	bool less(int idx1, int idx2) const {
		return info.rank[idx1] < info.rank[idx2];
	}
};
