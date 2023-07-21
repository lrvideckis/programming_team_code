/** @file */
#pragma once
#include "manacher.hpp"
template <class T> struct pal_query {
    int n;
    vector<int> man; //TODO: documentation
    //vector<int> longest; TODO /**< s.substr(i, i + longest[i]) = longest palindrome starting at i */
    /**
     * @param s string/array
     * @time O(n)
     * @space O(n) for `man` and `longest` arrays
     */
    pal_query(const T& s) : n(ssize(s)), man(manacher(s))/*, longest(n, 1)*/ {
        /*
        for (int i = n - 2; i >= 0; i--) {
            longest[i] = min(longest[i + 1] + 2, n - i);
            while(!is_pal(i, i + longest[i])) longest[i]--;
        }
        */
    }
    /**
     * @param le,ri defines substring [le,ri)
     * @returns 1 iff s.substr(le, ri - le) is a palindrome
     * @time O(1)
     * @space O(1)
     */
    inline bool is_pal(int le, int ri) const {
        assert(0 <= le && le <= ri && ri <= n);
        return (le == ri ? 1 : man[le + ri - 1] <= le);
    }
};
