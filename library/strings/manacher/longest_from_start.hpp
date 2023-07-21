/** @file */
#pragma once
#include "is_palindrome.hpp"
/**
 * @code{.cpp}
 *     string s;
 *     vector<int> man(manacher(s)), longest(longest_from_start(man));
 *     // or
 *     vector<int> arr;
 *     vector<int> man(manacher(arr)), longest(longest_from_start(man));
 * @endcode
 *
 * @param man manacher array
 * @returns longest where:
 *      - s.substr(i, i + longest[i]) is a palindrome
 *      - s.substr(i, i + j) is not a palindrome, if j > longest[i]
 * @time O(n)
 * @space an O(n) vector is allocated and returned
 */
vector<int> longest_from_start(const vector<int>& man) {
    int n = (ssize(man) + 1) / 2;
    vector<int> longest(n, 1);
    for (int i = n - 2; i >= 0; i--) {
        longest[i] = min(longest[i + 1] + 2, n - i);
        while(!is_pal(man, i, i + longest[i])) longest[i]--;
    }
    return longest;
}
