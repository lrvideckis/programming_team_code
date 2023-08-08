/** @file */
#pragma once
#include "../lcp_query.hpp"
#include "match.hpp"
/**
 * @param lq lcp query struct
 * @param substrs this defines query string t as:
 *     s.substr(substrs[0].first, substrs[0].second - substrs[0].first) +
 *     s.substr(substrs[1].first, substrs[1].second - substrs[1].first) +
 *     ...
 *     s.substr(substrs.back().first, substrs.back().second - substrs.back().first)
 * @returns see match
 * @time O(ssize(substrs) * log(|s|))
 * @space O(1)
 */
template <class T> inline match find_substrs_concated(const lcp_query<T>& lq,
        const vector<pair<int, int>>& substrs) {
    using dt = array<int, 3>;
    const auto& sa = lq.sa;
    int n = ssize(sa), sa_le = 0, sa_ri = n, str_le = 0, str_ri = 0, sum_len = 0;
    auto cmp = [&](int i, const dt & x) -> bool {
        int j = i + sum_len, lcp = min(lq.get_lcp(j, x[0]), x[1]);
        if (lcp + sum_len > str_ri - str_le) str_le = i, str_ri = j + lcp;
        if (lcp < min(n - j, x[1])) return lq.sa_inv[j] - lq.sa_inv[x[0]] < x[2];
        return x[2] ^ (n - j < x[1]);
    };
    for (auto [le, ri] : substrs) {
        assert(0 <= le && le <= ri && ri <= n);
        sa_le = int(lower_bound(begin(sa) + sa_le, begin(sa) + sa_ri, dt{le, ri - le, 0}, cmp) - begin(sa));
        sa_ri = int(lower_bound(begin(sa) + sa_le, begin(sa) + sa_ri, dt{le, ri - le, 1}, cmp) - begin(sa));
        sum_len += ri - le;
    }
    return {sa_le, sa_ri, str_le, str_ri};
}
