/** @file */
#pragma once
#include "lcp_query.hpp"
/**
 * @param s string/array
 * @param lq lcp query struct
 * @param s_le1,s_ri1 first substring [s_le1, s_ri1)
 * @param s_le2,s_ri2 second substring [s_le2, s_ri2)
 * @returns a value `cmp` where:
 *     - cmp < 0 iff s.substr(s_le1, s_ri1 - s_le1) < s.substr(s_le2, s_ri2 - s_le2)
 *     - cmp = 0 iff s.substr(s_le1, s_ri1 - s_le1) = s.substr(s_le2, s_ri2 - s_le2)
 *     - cmp > 0 iff s.substr(s_le1, s_ri1 - s_le1) > s.substr(s_le2, s_ri2 - s_le2)
 * @time O(1)
 * @space O(1)
 */
template <class T> inline int substr_cmp(const lcp_query<T>& lq,
        int s_le1, int s_ri1, int s_le2, int s_ri2) {
    const auto& sa_inv = lq.sf.sa_inv;
    assert(0 <= s_le1 && s_le1 <= s_ri1 && s_ri1 <= ssize(sa_inv));
    assert(0 <= s_le2 && s_le2 <= s_ri2 && s_ri2 <= ssize(sa_inv));
    int len1 = s_ri1 - s_le1;
    int len2 = s_ri2 - s_le2;
    return lq.get_lcp(s_le1, s_le2) >= min(len1, len2) ?
           len1 - len2 : sa_inv[s_le1] - sa_inv[s_le2];
}
