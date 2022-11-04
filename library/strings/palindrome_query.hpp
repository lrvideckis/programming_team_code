#pragma once
#include "../../kactl/content/strings/Manacher.h"
struct pal_query {
	const int N;
	array<vi, 2> pal_len;
	/**
	 * @time O(n)
	 * @memory O(n)
	 */
	pal_query(const string& s) : N(ssize(s)), pal_len(manacher(s)) {}
	/**
	 * Returns 1 if substring s[le...ri) is a palindrome.
	 * Returns 1 when le == ri.
	 * @time O(1)
	 */
	bool is_pal(int le, int ri) const {
		assert(0 <= le && le <= ri && ri <= N);
		int len = ri - le;
		return pal_len[len & 1][le + len / 2] >= len / 2;
	}
};
