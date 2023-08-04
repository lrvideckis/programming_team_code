/** @file */
#pragma once
#include "find_substr.hpp"
#include "substr_cmp.hpp"
template <class T> inline pair<int, int> find_substrs_concated(const lcp_query<T>& lq,
        int s_le1, int s_ri1, int s_le2, int s_ri2) {

    int n = ssize(lq.sf.sa);

    assert(0 <= s_le1 && s_le1 <= s_ri1 && s_ri1 <= n);
    assert(0 <= s_le2 && s_le2 <= s_ri2 && s_ri2 <= n);

    //TODO: find way to remove these base cases ?
    if (s_le1 == n) return find_substr(lq, s_le2, s_ri2);
    if (s_le2 == n) return find_substr(lq, s_le1, s_ri1);

    auto [le, ri] = find_substr(lq, s_le1, s_ri1);//TODO: return this in the above base case
    if(le == ri) return {le, ri};//TODO: remove?

    int len1 = s_ri1 - s_le1;
    int len2 = s_ri2 - s_le2;

    auto cmp = [&](int i, int cmp_val) -> bool {
        return s.compare(i, ssize(t), t) < cmp_val;
    };
    auto le = lower_bound(begin(info.sa), end(info.sa), 0, cmp);
    auto ri = lower_bound(le, end(info.sa), 1, cmp);
    return {le - begin(info.sa), ri - begin(info.sa)};

    return {le_it - begin(lq.sf.sa), ri_it - begin(lq.sf.sa)};
}
