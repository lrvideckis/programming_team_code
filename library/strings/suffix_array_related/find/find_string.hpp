/** @file */
#pragma once
#include "../suffix_array.hpp"
#include "match.hpp"
/**
 * @see https://github.com/yosupo06/Algorithm/blob /master/src/string/suffixarray.hpp
 *
 * @code{.cpp}
 *     string s;
 *     auto [sa, sa_inv] = get_sa(s, 256);
 *     string t;
 *     match m = find_str(s, sa, t);
 *     // or
 *     vector<int> arr;
 *     auto [sa, sa_inv] = get_sa(arr, 100'005);
 *     vector<int> t;
 *     match m = find_str(arr, sa, t);
 * @endcode
 *
 * @param s,sa string/array and its suffix array
 * @param t needle
 * @time O(|t| * log(|s|))
 * @space O(1)
 */
template <class T> inline match find_str(const T& s, const vector<int>& sa, const T& t) {
    int str_le = 0, str_ri = 0;
    auto cmp = [&](int i, int cmp_val) -> bool {
        auto [it_s, it_t] = mismatch(begin(s) + i, end(s), begin(t), end(t));
        if (it_s - begin(s) - i > str_ri - str_le)
            str_le = i, str_ri = int(it_s - begin(s));
        if (it_s != end(s) && it_t != end(t)) return *it_s -* it_t < cmp_val;
        if (cmp_val == 0) return it_s == end(s) && it_t != end(t);
        return it_t == end(t);
    };
    int sa_le = int(lower_bound(begin(sa), end(sa), 0, cmp) - begin(sa));
    int sa_ri = int(lower_bound(begin(sa) + sa_le, end(sa), 1, cmp) - begin(sa));
    return {sa_le, sa_ri, str_le, str_ri};
}
