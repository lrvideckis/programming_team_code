/** @file */
#pragma once
#include "../../data_structures/sparse_table.hpp"
#include "suffix_array.hpp"
#include "longest_common_prefix_array.hpp"
/**
 * Various queries you can do based on suffix array.
 * @code{.cpp}
 *     string s;
 *     sa_query saq(s, 256);
 *     vector<int> arr;
 *     sa_query saq(arr, 100'005);
 * @endcode
 */
template <typename T> struct sa_query {
    T s;
    vector<int> sa, sa_inv, lcp;
    RMQ<int> rmq_sa, rmq_lcp;
    /**
     * @param a_s,max_val string/array with 0 <= s[i] < max_val
     * @time O((n log n) + max_val)
     * @space O(n log n) for RMQ's; a O(max_val) vector `freq` is used temporarily during get_sa
     */
    sa_query(const T& a_s, int max_val) : s(a_s) {
        tie(sa, sa_inv) = get_sa(s, max_val);
        lcp = get_lcp_array(s, sa, sa_inv);
        rmq_sa = RMQ<int>(sa, [](int x, int y) -> int {return min(x, y);});
        rmq_lcp = RMQ<int>(lcp, [](int x, int y) -> int {return min(x, y);});
    }
    /**
     * @param i1,i2 starting 0-based-indexes of suffixes
     * @returns max integer k such that s.substr(i1, k) == s.substr(i2, k)
     * @time O(1)
     * @space O(1)
     */
    inline int get_lcp(int i1, int i2) const {
        if (i1 == i2) return ssize(s) - i1;
        auto [le, ri] = minmax(sa_inv[i1], sa_inv[i2]);
        return rmq_lcp.query(le, ri);
    }
    /**
     *
     * @param i1,i2 starting 0-based-indexes of suffixes
     * @returns 1 iff suffix s.substr(i1) < s.substr(i2)
     * @time O(1)
     * @space O(1)
     */
    inline bool less(int i1, int i2) const {
        return sa_inv[i1] < sa_inv[i2];
    }
    /**
     * @param str_le,str_ri defines a substring [str_le, str_ri) of s
     * @returns a range [le, ri) such that:
     * - for all i in [le, ri): s.substr(str_le, str_ri - str_le) == s.substr(sa[i], str_ri - str_le)
     * - `ri - le` is the # of matches of s.substr(str_le, str_ri - str_le) in s.
     * @time O(log(|s|))
     * @space O(1)
     */
    inline pair<int, int> find_substr(int str_le, int str_ri) const {
        assert(0 <= str_le && str_le <= str_ri && str_ri <= ssize(s));
        if (str_le == ssize(s)) return {0, ssize(s)};
        auto cmp = [&](int i, bool flip) -> bool {
            return (get_lcp(i, str_le) < str_ri - str_le) ^ flip;
        };
        auto le = lower_bound(begin(sa), begin(sa) + sa_inv[str_le], 0, cmp);
        auto ri = lower_bound(begin(sa) + sa_inv[str_le] + 1, end(sa), 1, cmp);
        return {le - begin(sa), ri - begin(sa)};
    }
    /**
     * @see https://github.com/yosupo06/Algorithm/blob /master/src/string/suffixarray.hpp
     * @param t needle
     * @returns range [le, ri) such that:
     * - for all i in [le, ri): t == s.substr(sa[i], ssize(t))
     * - `ri - le` is the # of matches of t in s.
     * @time O(|t| * log(|s|))
     * @space O(1)
     */
    inline pair<int, int> find_str(const T& t) const {
        auto cmp = [&](int i, int cmp_val) -> bool {
            return s.compare(i, ssize(t), t) < cmp_val;
        };
        auto le = lower_bound(begin(sa), end(sa), 0, cmp);
        auto ri = lower_bound(le, end(sa), 1, cmp);
        return {le - begin(sa), ri - begin(sa)};
    }
    /**
     * @param t needle
     * @returns min i such that t == s.substr(i, ssize(t)) or -1. For example,
     * replace RMQ with kth-smallest PST/Wavelet to solve
     * https://open.kattis.com/problems /anothersubstringqueryproblem
     * @time O(|t| * log(|s|))
     * @space O(1)
     */
    inline int find_first(const T& t) const {
        auto [le, ri] = find_str(t);
        if (le == ri) return -1;
        return rmq_sa.query(le, ri);
    }
};
