/** @file */
#pragma once
#include "prefix_function.hpp"
/**
 * @code{.cpp}
       string s;
       KMP kmp(s);
       vector<int> a;
       KMP kmp(a);
 * @endcode
 * KMP doubling trick: to check if 2 arrays are rotationally equivalent: run
 * kmp with one array as the needle and the other array doubled (excluding the
 * first & last characters) as the haystack or just use kactl's min rotation
 * code.
 */
//NOLINTNEXTLINE(readability-identifier-naming)
template <class T> struct KMP {
    T needle;
    vector<int> pi;
    /**
     * @param _needle string to be searched for inside haystack
     * @time O(|needle|)
     * @space O(|needle|) for `needle` and `pi` arrays
     */
    KMP(const T& _needle) : needle(_needle), pi(prefix_function(needle)) {}
    /**
     * @param haystack usually |needle| <= |haystack|
     * @returns array `matches` where:
     * haystack.substr(matches[i], ssize(needle)) == needle
     * @time O(|haystack|)
     * @space besides O(|haystack|) param, this function allocates/returns an
     * array of size (# matches), at worst O(|haystack|)
     */
    vector<int> find_str(const T& haystack) {
        vector<int> matches;
        for (int i = 0, j = 0; i < ssize(haystack); i++) {
            while (j > 0 && needle[j] != haystack[i]) j = pi[j - 1];
            j += (needle[j] == haystack[i]);
            if (j == ssize(needle)) {
                matches.push_back(i - ssize(needle) + 1);
                j = pi[j - 1];
            }
        }
        return matches;
    }
};
