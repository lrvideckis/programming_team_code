/** @file */
#pragma once
#include "constructor.hpp"
/**
 * @param i1,i2 starting 0-based-indexes of suffixes
 * @returns max integer k such that s.substr(i1, k) == s.substr(i2, k)
 * @time O(1)
 * @space O(1)
 */
inline int get_lcp(const sa_query& sq, int i1, int i2) {
    if (i1 == i2) return ssize(s) - i1;
    auto [le, ri] = minmax(sa_inv[i1], sa_inv[i2]);
    return rmq_lcp.query(le, ri);
}
