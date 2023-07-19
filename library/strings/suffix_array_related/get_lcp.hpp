/** @file */
#pragma once
#include "../../data_structures/sparse_table.hpp"
#include "suffix_array.hpp"
#include "longest_common_prefix_array.hpp"
/**
 *
 * @code{.cpp}
 *     string s;
 *     auto [sa, sa_inv] = get_sa(s, 256);
 *     vector<int> lcp = get_lcp_array({sa, sa_inv}, s);
 *     int len = get_lcp(sa_inv, lcp, i1, i2);
 *     // or
 *     vector<int> arr;
 *     auto [sa, sa_inv] = get_sa(arr, 100'005);
 *     vector<int> lcp = get_lcp_array({sa, sa_inv}, arr);
 *     int len = get_lcp(sa_inv, lcp, i1, i2);
 * @endcode
 *
 * @param i1,i2 starting 0-based-indexes of suffixes
 * @returns max integer k such that s.substr(i1, k) == s.substr(i2, k)
 * @time O(1)
 * @space O(1)
 */
inline int get_lcp(const vector<int>& sa_inv, const vector<int>& lcp, int i1, int i2) {
    static RMQ<int> rmq_lcp(lcp, [](int x, int y) -> int {return min(x, y);});
    if (i1 == i2) return ssize(sa_inv) - i1;
    auto [le, ri] = minmax(sa_inv[i1], sa_inv[i2]);
    return rmq_lcp.query(le, ri);
}
