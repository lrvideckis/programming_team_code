/** @file */
#pragma once
#include "../../data_structures/sparse_table.hpp"
#include "manacher.hpp"
/**
 * @see https://codeforces.com/blog/entry/63105#comment-470339
 */
//TODO test
template <class T> struct longest_pal {
    int n;
    vector<int> man;
    RMQ<int> rmq_le, rmq_ri;
    /**
     * @param s string/array
     * @time O(n log n)
     * @space O(n log n) TODO
     */
    longest_pal(const T& s) : n(ssize(s)), man(manacher(s)), rmq_le(man, [](int x, int y) -> int {return min(x,y);}) {
    }
    /**
     * @param str_le,str_ri defines substring [str_le,str_ri)
     * @returns returns substring [le, ri) such that:
     *    - str_le <= le && ri <= str_ri
     *    - s.substr(le, ri - le) is the longest palindromic substring of s.substr(str_le, str_ri - str_le)
     *    - if multiple longest palindromic substrings, le is minimized
     * @time O(1)
     * @space O(1)
     */
    inline int get_longest(int str_le, int str_ri) const {
        assert(0 <= le && le <= ri && ri <= n);
        int str_mi = (str_ri + str_le) / 2;
        return rmq_le.query(
    }
};
