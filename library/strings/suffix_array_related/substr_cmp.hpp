/** @file */
#pragma once
#include "suf_cmp.hpp"
#include "lcp_query.hpp"
inline bool substr_cmp(const lcp_query<T>& lq,
                       int str_le1, int str_ri1, int str_le2, int str_ri2) {
    int len1 = str_ri1 - str_le1;
    int len2 = str_ri2 - str_le2;
    int mn_len = min(len1, len2);
    return lq.get_lcp(str_le1, str_le2) >= mn_len ? len1 < len2 ? suf_cmp(lq.sf.sa_inv, str_le1, str_le2);
}
