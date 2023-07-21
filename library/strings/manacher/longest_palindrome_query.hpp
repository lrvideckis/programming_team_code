/** @file */
#pragma once
#include "manacher.hpp"
/**
 * Interface on top of manacher array
 */
template <class T> struct longest_pal {
    int n;
    vector<int> man; //TODO: documentation
    //vector<int> longest; TODO /**< s.substr(i, i + longest[i]) = longest palindrome starting at i */
    /**
     * @param s string/array
     * @time O(n)
     * @space O(n) for `man` and `longest` arrays
     */
    longest_pal(const T& s) : n(ssize(s)), man(manacher(s))/*, longest(n, 1)*/ {
        /*
        for (int i = n - 2; i >= 0; i--) {
            longest[i] = min(longest[i + 1] + 2, n - i);
            while(!is_pal(i, i + longest[i])) longest[i]--;
        }
        */
    }
    /**
     * @param str_le,str_ri defines substring [str_le,str_ri)
     * @returns returns range [le, ri) such that.
     *    - str_le <= le && le <= ri && ri <= str_ri
     *    - s.substr(le, ri - le) is the longest palindromic substring of s.substr(str_le, str_ri - str_le)
     * @time O(1)
     * @space O(1)
     */
    inline pair<int, int> long_pal(int str_le, int str_ri) const {
        assert(0 <= le && le <= ri && ri <= n);
        return (le == ri ? 1 : man[le + ri - 1] <= le);
    }
};
