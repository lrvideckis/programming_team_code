/** @file */
#pragma once
#include "../../data_structures/sparse_table.hpp"
#include "find_str.hpp"
/**
 * Query for first substring match. Although, mainly an example of
 * how to use `find_str`
 */
template <typename T> struct find_first {
    T s;
    suf sf;
    RMQ<int> rmq;
    /**
     * @param a_s,max_val string/array such that 0 <= s[i] < max_val
     * @time O((n log n) + max_val)
     * @space O(n log n) for RMQ's; a O(max_val) vector `freq` is used temporarily during get_sa
     */
    find_first(const T& a_s, int max_val) : s(a_s), sf(get_sa(s, max_val)),
        rmq(sf.sa, [](int x, int y) -> int {return min(x, y);}) {}
    /**
     * @param t needle
     * @returns min i such that t == s.substr(i, ssize(t)) or -1. For example,
     * replace RMQ with kth-smallest PST/Wavelet to solve
     * https://open.kattis.com/problems /anothersubstringqueryproblem
     * @time O(|t| * log(|s|))
     * @space O(1)
     */
    inline int first_match(const T& t) const {
        auto [le, ri] = find_str(s, sf.sa, t);
        if (le == ri) return -1;
        return rmq.query(le, ri);
    }
};
