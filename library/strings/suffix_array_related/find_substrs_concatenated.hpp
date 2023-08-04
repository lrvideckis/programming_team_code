/** @file */
#pragma once
#include "substr_cmp.hpp"
template <class T> inline pair<int, int> find_substrs_concated(const T& s, const lcp_query<T>& lq,
        const vector<pair<int, int>>& substrs) {
    const auto& sa = lq.sf.sa;
    int n = ssize(sa), le = 0, ri = n, sum_len = 0;
    for (auto [s_le, s_ri] : substrs) {
        assert(0 <= s_le && s_le <= s_ri && s_ri <= n);
        //if (s_le == n) continue;//TODO: will substr_cmp handle this?
        //TODO: test performance of lambda-initialization in loop
        auto cmp = [&](int i, int cmp_val) -> bool {
            i += sum_len;
            return substr_cmp(s, lq, i, min(i + s_ri - s_le, n), s_le, s_ri) < cmp_val;
        };
        le = int(lower_bound(begin(sa) + le, begin(sa) + ri, 0, cmp) - begin(sa));
        ri = int(lower_bound(begin(sa) + le, begin(sa) + ri, 1, cmp) - begin(sa));
        sum_len += s_ri - s_le;
    }
    return {le, ri};
}
