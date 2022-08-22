#pragma once
#include "../../kactl/content/strings/Manacher.h"
struct pal_query {
	const int N;
	array<vi, 2> pal_len;
	pal_query(const string& s) : N(s.size()), pal_len(manacher(s)) {}
	//returns 1 if substring s[l...r) is a palindrome
	//(returns 1 when l == r)
	bool is_pal(int l, int r) const {
		assert(0 <= l && l <= r && r <= N);
		int len = r - l;
		return pal_len[len & 1][l + len / 2] >= len / 2;
	}
};
