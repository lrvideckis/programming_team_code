#pragma once
#include "lcp_query.h"
struct pal_query {
	const int N;
	lcp_query lq;
	pal_query(const string& s) : N(s.size()), lq(s + string(s.rbegin(), s.rend())) {}
	//returns 1 if substring s[l...r) is a palindrome
	bool is_pal(int l, int r) const {
		assert(0 <= l && l <= r && r <= N);
		return l == r ? 1 : lq.longest_common_prefix(l, 2 * N - r) >= r - l;
	}
};
