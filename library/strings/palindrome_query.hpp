/** @file */
#pragma once
#include "../../kactl/content/strings/Manacher.h"
/**
 * More intuitive interface to manacher than raw array.
 */
struct pal_query {
	const int N;
	array<vi, 2> pal_len; /**< half the length of palindrome for each center */
	/**
	 * @param s string
	 * @time O(n)
	 * @memory O(n)
	 */
	pal_query(const string& s) : N(ssize(s)), pal_len(manacher(s)) {}
	/**
	 * @param le,ri defines substring [le,ri)
	 * @returns 1 iff the substring is a palindrome (so 1 when le == ri)
	 * @time O(1)
	 */
	bool is_pal(int le, int ri) const {
		assert(0 <= le && le <= ri && ri <= N);
		int len = ri - le;
		return pal_len[len & 1][le + len / 2] >= len / 2;
	}
};
