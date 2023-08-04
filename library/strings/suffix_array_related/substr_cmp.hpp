/** @file */
#pragma once
#include "lcp_query.hpp"
template <class T> inline int substr_cmp(const T& s, const lcp_query<T>& lq,
                       int s_le1, int s_ri1, int s_le2, int s_ri2) {
    int len1 = s_ri1 - s_le1;
    int len2 = s_ri2 - s_le2;
    int lcp = lq.get_lcp(s_le1, s_le2);
    return lcp >= min(len1, len2) ? len1 - len2 : s[s_le1 + lcp] - s[s_le2 + lcp];
}
