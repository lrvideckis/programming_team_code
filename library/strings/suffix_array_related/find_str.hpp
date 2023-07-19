/** @file */
#pragma once
#include "suffix_array.hpp"
/**
 * @see https://github.com/yosupo06/Algorithm/blob /master/src/string/suffixarray.hpp
 *
 * @code{.cpp}
 *     string s;
 *     auto [sa, sa_inv] = get_sa(s, 256);
 *     string t;
 *     auto [le, ri] = find_str(s, sa, t);
 *     // or
 *     vector<int> arr;
 *     auto [sa, sa_inv] = get_sa(arr, 100'005);
 *     vector<int> t;
 *     auto [le, ri] = find_str(arr, sa, t);
 * @endcode
 *
 * @param t needle
 * @returns range [le, ri) such that:
 * - for all i in [le, ri): t == s.substr(sa[i], ssize(t))
 * - `ri - le` is the # of matches of t in s.
 * note find_str("") returns [0, ssize(s))
 * @time O(|t| * log(|s|))
 * @space O(1)
 */
template <typename T> inline pair<int, int> find_str(const T& s, const vector<int>& sa, const T& t) {
    auto cmp = [&](int i, int cmp_val) -> bool {
        auto [it_t, it_s] = mismatch(begin(t), end(t), begin(s) + i, end(s));
        return 1;//TODO
    };
    auto le = lower_bound(begin(sa), end(sa), 0, cmp);
    auto ri = lower_bound(le, end(sa), 1, cmp);
    return {le - begin(sa), ri - begin(sa)};
}
