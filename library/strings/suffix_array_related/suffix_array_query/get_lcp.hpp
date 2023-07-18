/** @file */
#pragma once
#include "constructor.hpp"
/**
 * @param i1,i2 starting 0-based-indexes of suffixes
 * @returns max integer k such that s.substr(i1, k) == s.substr(i2, k)
 * @time O(1)
 * @space O(1)
 */
template <typename T> inline int get_lcp(const sa_query<T>& sq, int i1, int i2) {
    if (i1 == i2) return ssize(sq.s) - i1;
    auto [le, ri] = minmax(sq.sa_inv[i1], sq.sa_inv[i2]);
    return sq.rmq_lcp.query(le, ri);
}
