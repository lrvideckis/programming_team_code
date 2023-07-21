/** @file */
#pragma once
#include "manacher.hpp"
/**
 * @see https://codeforces.com/blog/entry/63105#comment-470339
 */
template <class T> struct longest_pal {
    int n;
    vector<int> man; //TODO: documentation
    /**
     * @param s string/array
     * @time O(n)
     * @space O(n) TODO
     */
    longest_pal(const T& s) : n(ssize(s)), man(manacher(s)) {
        //TODO
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
    inline pair<int, int> get_longest(int str_le, int str_ri) const {
        //TODO
    }
};
