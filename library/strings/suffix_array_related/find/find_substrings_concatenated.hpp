/** @file */
#pragma once
#include "../compare/compare_substrings.hpp"
#include "match.hpp"
/**
 * @param lq lcp query struct
 * @param substrs array of substrings [substrs[i].first, substrs[i].second)
 * @time O(ssize(substrs) * log(|s|))
 * @space O(1)
 */
template <class T> inline match find_substrs_concated(const lcp_query<T>& lq,
        const vector<pair<int, int>>& substrs) {
    using dt = array<int, 3>;
    const auto& sa = lq.sa;
    int n = ssize(sa), sa_le = 0, sa_ri = n, str_le = 0, str_ri = 0, sum_len = 0;
    auto cmp = [&](int i, const dt & x) -> bool {
        int j = i + sum_len;
        //TODO lq.get_lcp is called twice: once here, once in substr_cmp
        int len = min(lq.get_lcp(j, x[0]), x[1] - x[0]);
        if (len + sum_len > str_ri - str_le)
            str_le = i, str_ri = j + len;
        return substr_cmp(lq, j, min(j + x[1] - x[0], n), x[0], x[1]) < x[2];
    };
    for (auto [le, ri] : substrs) {
        assert(0 <= le && le <= ri && ri <= n);
        sa_le = int(lower_bound(begin(sa) + sa_le, begin(sa) + sa_ri, dt{le, ri, 0}, cmp) - begin(sa));
        sa_ri = int(lower_bound(begin(sa) + sa_le, begin(sa) + sa_ri, dt{le, ri, 1}, cmp) - begin(sa));
        sum_len += ri - le;
    }
    return {sa_le, sa_ri, str_le, str_ri};
}
