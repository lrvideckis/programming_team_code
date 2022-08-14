#include "lcp_queries.h"
struct pal_query {
	const int n;
	lcp_queries lq;
	pal_query(const string& s) : n(s.size()), lq(s + string(s.rbegin(), s.rend())) {}
	//returns 1 if substring s[l...r) is a palendrome
	bool is_pal(int l, int r) const {
		assert(0 <= l && l <= r && r <= n);
		return l == r ? 1 : lq.longest_common_prefix(l, 2 * n - r) >= r - l;
	}
};
