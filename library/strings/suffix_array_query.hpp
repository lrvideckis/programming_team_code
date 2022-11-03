#pragma once
#include "../../hackpack-cpp/content/strings/SuffixArray.h"
#include "../range_data_structures/rmq.hpp"
//various queries you can do based on Suffix Array
/*
suffixes of "banana":

0 banana$
1 anana$
2 nana$
3 ana$
4 na$
5 a$
6 $

sorted:
          lcp
          0
6 $
          0
5 a$
  |       1
3 ana$
  |||     3
1 anana$
          0
0 banana$
          0
4 na$
  ||      2
2 nana$

suffix array = [6, 5, 3, 1, 0, 4, 2]
lcp array = [0, 0, 1, 3, 0, 0, 2]
*/
struct sa_query {
	string s;
	SuffixArray info;
	RMQ<int> rmq_lcp, rmq_sa;
	/**
	 * @time O(n log n)
	 * @memory O(n log n) - because of RMQ
	 */
	sa_query(string& a_s) :
		s(a_s),
		info(SuffixArray(s)),
		rmq_lcp(vi(info.lcp.begin() + 1, info.lcp.end()), [](int i, int j) -> int {return min(i, j);}),
		rmq_sa(info.sa, [](int i, int j) -> int {return min(i, j);}) {}
	/**
	 * @brief Returns length of longest common prefix of suffixes s[idx1...N),
	 *     s[idx2...N), 0-based indexing.
	 * @trick To check if two substrings s[l1..r1), s[l2..r2) are equal:
	 *     r1-l1 == r2-l2 && longest_common_prefix(l1, l2) >= r1-l1
	 * @time O(1)
	 */
	int get_lcp(int idx1, int idx2) const {
		if (idx1 == idx2)
			return ssize(s) - idx1;
		auto [le, ri] = minmax(info.rank[idx1], info.rank[idx2]);
		return rmq_lcp.query(le, ri);
	}
	/**
	 * @brief Returns 1 if suffix s[idx1 ... N) < s[idx2 ... N) (so 0 if
	 *     idx1 == idx2).
	 * @time O(1)
	 */
	bool less(int idx1, int idx2) const {
		return info.rank[idx1] < info.rank[idx2];
	}
	/**
	 * @brief Returns range [le, ri) such that:
	 *   - for all i in [le, ri): t == s.substr(info.sa[i], ssize(t))
	 *   - `ri - le` is the # of matches of t in s is okay.
	 * @time O(|t| * log(|s|))
	 */
	pair<int, int> find(const string& t) const {
		auto cmp = [&](int i, int cmp_val) -> bool {
			return s.compare(i, ssize(t), t) < cmp_val;
		};
		auto le = lower_bound(info.sa.begin(), info.sa.end(), 0, cmp);
		auto ri = lower_bound(le, info.sa.end(), 1, cmp);
		return {le - info.sa.begin(), ri - info.sa.begin()};
	}
	/**
	 * @brief Returns min i such that t == s.substr(i, ssize(t)) or -1. For
	 *     example, replace RMQ with kth-smallest PST/Wavelet to solve
	 *     https://open.kattis.com/problems/anothersubstringqueryproblem
	 * @time O(|t| * log(|s|))
	 */
	int find_first(const string& t) const {
		auto [le, ri] = find(t);
		if (le == ri)
			return -1;
		return rmq_sa.query(le, ri);
	}
};
