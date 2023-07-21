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
 * @param i1,i2 starting 0-based-indexes of suffixes
 * @returns 1 iff suffix s.substr(i1) < s.substr(i2)
 * @time O(1)
 * @space O(1)
 */
inline bool suf_cmp(const vector<int>& sa_inv, int i1, int i2) {
    return sa_inv[i1] < sa_inv[i2];
}
