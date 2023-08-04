/** @file */
#pragma once
#include "substr_cmp.hpp"
template <class T> inline pair<int, int> find_substrs_concated(const T& s, const lcp_query<T>& lq,
        const vector<pair<int, int>>& substrs) {
    using dt = array<int, 3>;
    const auto& sa = lq.sf.sa;
    int n = ssize(sa), le = 0, ri = n, sum_len = 0;
    auto cmp = [&](int i, const dt& x) -> bool {
        i += sum_len;
        return substr_cmp(s, lq, i, min(i + x[1] - x[0], n), x[0], x[1]) < x[2];
    };
    for (auto [s_le, s_ri] : substrs) {
        assert(0 <= s_le && s_le <= s_ri && s_ri <= n);
        le = int(lower_bound(begin(sa) + le, begin(sa) + ri, dt{s_le, s_ri, 0}, cmp) - begin(sa));
        ri = int(lower_bound(begin(sa) + le, begin(sa) + ri, dt{s_le, s_ri, 1}, cmp) - begin(sa));
        sum_len += s_ri - s_le;
    }
    return {le, ri};
}
