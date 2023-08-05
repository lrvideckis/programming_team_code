/** @file */
#pragma once
#include "substr_cmp.hpp"
/**
 * @param s string/array
 * @param lq lcp query struct
 * @param substrs array of substrings [substrs[i].first, substrs[i].second)
 * @returns range [le, ri) such that:
 *     - for all i in [le, ri): t == s.substr(sa[i], ssize(t))
 *     - `ri - le` is the # of matches of t in s.
 *     where t = s.substr(substrs[0].first, substrs[0].second - substrs[0].first) +
 *               s.substr(substrs[1].first, substrs[1].second - substrs[1].first) +
 *               ...
 *               s.substr(substrs.back().first, substrs.back().second - substrs.back().first)
 * @time O(ssize(substrs) * log(|s|))
 * @space O(1)
 */
template <class T> inline pair<int, int> find_substrs_concated(const lcp_query<T>& lq,
        const vector<pair<int, int>>& substrs) {
    using dt = array<int, 3>;
    const auto& sa = lq.sf.sa;
    int n = ssize(sa), le = 0, ri = n, sum_len = 0;
    auto cmp = [&](int i, const dt & x) -> bool {
        i += sum_len;
        return substr_cmp(lq, i, min(i + x[1] - x[0], n), x[0], x[1]) < x[2];
    };
    for (auto [s_le, s_ri] : substrs) {
        assert(0 <= s_le && s_le <= s_ri && s_ri <= n);
        le = int(lower_bound(begin(sa) + le, begin(sa) + ri, dt{s_le, s_ri, 0}, cmp) - begin(sa));
        ri = int(lower_bound(begin(sa) + le, begin(sa) + ri, dt{s_le, s_ri, 1}, cmp) - begin(sa));
        sum_len += s_ri - s_le;
    }
    return {le, ri};
}
