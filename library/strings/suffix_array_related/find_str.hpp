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
 * @param s,sa string/array and its suffix array
 * @param t needle
 * @returns range [le, ri) such that:
 *     - for all i in [le, ri): t == s.substr(sa[i], ssize(t))
 *     - `ri - le` is the # of matches of t in s.
 * note find_str(s, sa, string("")) returns [0, ssize(s))
 * @time O(|t| * log(|s|))
 * @space O(1)
 */
template <class T> inline pair<int, int> find_str(const T& s, const vector<int>& sa, const T& t) {
    auto le = lower_bound(begin(sa), end(sa), 0, [&](int i, int) -> bool {
        return lexicographical_compare(begin(s) + i, end(s), begin(t), end(t));
    });
    auto ri = lower_bound(le, end(sa), 0, [&](int i, int) -> bool {
        return mismatch(begin(s) + i, end(s), begin(t), end(t)).second == end(t);
    });
    return {le - begin(sa), ri - begin(sa)};
}
