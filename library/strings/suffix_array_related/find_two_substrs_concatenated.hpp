/** @file */
#pragma once
#include "find_substr.hpp"
template <class T> inline pair<int, int> find_substrs_concated(const lcp_query<T>& lq,
        int str_le1, int str_ri1, int str_le2, int str_ri2) {

    int n = ssize(lq.sf.sa);

    assert(0 <= str_le1 && str_le1 <= str_ri1 && str_ri1 <= n);
    assert(0 <= str_le2 && str_le2 <= str_ri2 && str_ri2 <= n);

    //TODO: find way to remove these base cases ?
    if (str_le1 == n) return find_substr(lq, str_le2, str_ri2);
    if (str_le2 == n) return find_substr(lq, str_le1, str_ri1);

    auto [le, ri] = find_substr(lq, str_le1, str_ri1);//TODO: return this in the above base case
    if(le == ri) return {le, ri};//TODO: remove?

    int len1 = str_ri1 - str_le1;
    int len2 = str_ri2 - str_le2;

    auto cmp1 = [&](int i, bool) -> bool {
        int len_match = len1;
        if (i + len1 == n) {
        }
        return lq.get_lcp(i + len1, str_le2) < len2;
    };
    auto le_it = lower_bound(begin(lq.sf.sa) + le, begin(lq.sf.sa) + ri, 0, cmp1);

    auto cmp2 = [&](int i, bool) -> bool {
        assert(i + len1 < n); //TODO: is this correct?
        return lq.get_lcp(i + len1, str_le2) >= len2;
    };
    auto ri_it = lower_bound(le_it, end(lq.sf.sa) + ri, 0, cmp2);

    return {le_it - begin(lq.sf.sa), ri_it - begin(lq.sf.sa)};
}
