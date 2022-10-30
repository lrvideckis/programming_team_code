#pragma once
#include "../../hackpack-cpp/content/strings/SuffixArray.h"
#include "../range_data_structures/rmq.hpp"
//computes suffix array, lcp array, and then sparse table over lcp array
//O(n log n)
struct str_query {
	string s;
	SuffixArray info;
	RMQ<int> rmq;
	str_query(string& a_s) : s(a_s), info(SuffixArray(s)), rmq(vi(info.lcp.begin() + 1, info.lcp.end()), [](int i, int j) -> int {return min(i, j);}) {}
	//length of longest common prefix of suffixes s[idx1 ... N), s[idx2 ... N), 0-based indexing
	//
	//You can check if two substrings s[l1..r1), s[l2..r2) are equal in O(1) by:
	//r1-l1 == r2-l2 && longest_common_prefix(l1, l2) >= r1-l1
	int get_lcp(int idx1, int idx2) const {
		if (idx1 == idx2)
			return ssize(s) - idx1;
		auto [le, ri] = minmax(info.rank[idx1], info.rank[idx2]);
		return rmq.query(le, ri);
	}
	//returns 1 if suffix s[idx1 ... N) < s[idx2 ... N)
	//(so 0 if idx1 == idx2)
	bool less(int idx1, int idx2) const {
		return info.rank[idx1] < info.rank[idx2];
	}
	//returns range [le, ri) such that:
	//	- for all i ∈ [le, ri): t == s.substr(info.sa[i], ssize(t))
	//	- `ri - le` is the # of matches of t in s
	//O(|t| * log(|s|))
	pair<int, int> find(const string& t) const {
		auto cmp = [&](int i, int cmp_val) -> bool {
			return s.compare(i, ssize(t), t) < cmp_val;
		};
		auto le = lower_bound(info.sa.begin(), info.sa.end(), 0, cmp);
		auto ri = lower_bound(info.sa.begin(), info.sa.end(), 1, cmp);
		return {le - info.sa.begin(), ri - info.sa.begin()};
	}
};
