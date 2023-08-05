/** @file */
#pragma once
#include "../lcp_query.hpp"
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
        int j = i + sum_len, len = x[1] - x[0], lcp = min(lq.get_lcp(j, x[0]), len);
        if (lcp + sum_len > str_ri - str_le)
            str_le = i, str_ri = j + lcp;
        if (lcp < min(n - j, len)) return lq.sa_inv[j] - lq.sa_inv[x[0]] < x[2];
        return x[2] ^ (n - j < len);
    };
    for (auto [le, ri] : substrs) {
        assert(0 <= le && le <= ri && ri <= n);
        sa_le = int(lower_bound(begin(sa) + sa_le, begin(sa) + sa_ri, dt{le, ri, 0}, cmp) - begin(sa));
        sa_ri = int(lower_bound(begin(sa) + sa_le, begin(sa) + sa_ri, dt{le, ri, 1}, cmp) - begin(sa));
        sum_len += ri - le;
    }
    return {sa_le, sa_ri, str_le, str_ri};
}
