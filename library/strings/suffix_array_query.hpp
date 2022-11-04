#pragma once
#include "suffix_array.hpp"
#include "../range_data_structures/rmq.hpp"
/**
 * Various queries you can do based on suffix array.
 * @see https://github.com/yosupo06/Algorithm/blob
 * /master/src/string/suffixarray.hpp
 */
template <typename T> struct sa_query {
	T s;
	suffix_array<T> info;
	RMQ<int> rmq_lcp, rmq_sa;
	/**
	 * Assumes 0 <= s[i] < max_val.
	 * @time O((nlogn) + max_val)
	 * @memory O((nlogn) + max_val) An O(max_val) size freq array is used
	 * temporarily during suffix array construction. Only O(n log n) memory is
	 * permanently stored by this struct.
	 */
	sa_query(const T& a_s, int max_val) :
		s(a_s),
		info(suffix_array(s, max_val)),
		rmq_lcp(info.lcp, [](int i, int j) -> int {return min(i, j);}),
		rmq_sa(info.sa, [](int i, int j) -> int {return min(i, j);}) {}
	/**
	 * Returns length of longest common prefix of suffixes s[idx1...N),
	 * s[idx2...N), 0-based indexing.
	 *
	 * To check if two substrings s[l1..r1), s[l2..r2) are equal:
	 * r1-l1 == r2-l2 && get_lcp(l1, l2) >= r1-l1
	 * @time O(1)
	 */
	int get_lcp(int idx1, int idx2) const {
		if (idx1 == idx2) return ssize(s) - idx1;
		auto [le, ri] = minmax(info.rank[idx1], info.rank[idx2]);
		return rmq_lcp.query(le, ri);
	}
	/**
	 * Returns 1 if suffix s[idx1 ... N) < s[idx2 ... N).
	 * Returns 0 if idx1 == idx2.
	 * @time O(1)
	 */
	bool less(int idx1, int idx2) const {
		return info.rank[idx1] < info.rank[idx2];
	}
	/**
	 * Returns range [le, ri) such that:
	 * - for all i in [le, ri): t == s.substr(info.sa[i], ssize(t))
	 * - `ri - le` is the # of matches of t in s is okay.
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
	 * Returns min i such that t == s.substr(i, ssize(t)) or -1. For example,
	 * replace RMQ with kth-smallest PST/Wavelet to solve
	 * https://open.kattis.com/problems/anothersubstringqueryproblem
	 * @time O(|t| * log(|s|))
	 */
	int find_first(const string& t) const {
		auto [le, ri] = find(t);
		if (le == ri) return -1;
		return rmq_sa.query(le, ri);
	}
};
