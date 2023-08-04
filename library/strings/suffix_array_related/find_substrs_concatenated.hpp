/** @file */
#pragma once
#include "find_substr.hpp"
#include "substr_cmp.hpp"
template <class T> inline pair<int, int> find_substrs_concated(const T& s, const lcp_query<T>& lq,
        const vector<pair<int, int>>& substrs) {
    const auto& sa = lq.sf.sa;
    int n = ssize(sa);
    //assert(0 <= s_le1 && s_le1 <= s_ri1 && s_ri1 <= n);
    //assert(0 <= s_le2 && s_le2 <= s_ri2 && s_ri2 <= n);
    auto [le, ri] = find_substr(lq, s_le1, s_ri1);
    int len1 = s_ri1 - s_le1;
    int len2 = s_ri2 - s_le2;
    auto cmp = [&](int i, int cmp_val) -> bool {
        i += len1;
        return substr_cmp(s, lq, i, min(i + len2, n), s_le2, s_ri2) < cmp_val;
    };
    le = int(lower_bound(begin(sa) + le, begin(sa) + ri, 0, cmp) - begin(sa));
    ri = int(lower_bound(begin(sa) + le, begin(sa) + ri, 1, cmp) - begin(sa));
    return {le, ri};
}
