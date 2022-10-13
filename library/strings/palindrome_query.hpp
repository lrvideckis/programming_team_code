#pragma once
#include "../../kactl/content/strings/Manacher.h"
struct pal_query {
	const int N;
	array<vi, 2> pal_len;
	pal_query(const string& s) : N(ssize(s)), pal_len(manacher(s)) {}
	//returns 1 if substring s[le...ri) is a palindrome
	//(returns 1 when le == ri)
	bool is_pal(int le, int ri) const {
		assert(0 <= le && le <= ri && ri <= N);
		int len = ri - le;
		return pal_len[len & 1][le + len / 2] >= len / 2;
	}
};
