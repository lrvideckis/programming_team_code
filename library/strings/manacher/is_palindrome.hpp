/** @file */
#pragma once
#include "manacher.hpp"
/**
 * @code{.cpp}
 *     string s;
 *     vector<int> man = manacher(s);
 *     bool pal = is_pal(man, le, ri);
 *     // or
 *     vector<int> arr;
 *     vector<int> man = manacher(arr);
 *     bool pal = is_pal(man, le, ri);
 * @endcode
 *
 * @param le,ri defines substring [le,ri)
 * @returns 1 iff s.substr(le, ri - le) is a palindrome
 * @time O(1)
 * @space O(1)
 */
inline bool is_pal(const vector<int>& man, int le, int ri) {
    //TODO: test with empty string
    //TODO: add to vector test
    assert(0 <= le && le <= ri && ri <= (ssize(man) + 1) / 2);
    return (le == ri ? 1 : man[le + ri - 1] <= le);
}
