/** @file */
#pragma once
#include "suffix_array.hpp"
/**
 * @code{.cpp}
 *     string s;
 *     auto [sa, sa_inv] = get_sa(s, 256);
 *     suf_cmp(sa_inv, i1, i2);
 *     // or
 *     vector<int> arr;
 *     auto [sa, sa_inv] = get_sa(arr, 100'005);
 *     suf_cmp(sa_inv, i1, i2);
 * @endcode
 *
 * @param sa_inv inverse permutation of suffix array
 * @param i1,i2 defines suffixes [i1, n), [i2, n), note passing i1,i2 = n is okay
 * @returns a value `cmp` where:
 *     - cmp < 0 iff s.substr(i1) < s.substr(i2)
 *     - cmp = 0 iff s.substr(i1) = s.substr(i2)
 *     - cmp > 0 iff s.substr(i1) > s.substr(i2)
 * @time O(1)
 * @space O(1)
 */
inline int suf_cmp(const vector<int>& sa_inv, int i1, int i2) {
    assert(0 <= min(i1, i2) && max(i1, i2) <= ssize(sa_inv));
    return max(i1, i2) == ssize(sa_inv) ? i2 - i1 : sa_inv[i1] - sa_inv[i2];
}
