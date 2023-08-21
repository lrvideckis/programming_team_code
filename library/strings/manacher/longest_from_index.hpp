/** @file */
#pragma once
#include "is_palindrome.hpp"
/**
 * @see https://github.com/brunomaletta/Biblioteca /blob/master/Codigo/Strings/manacher.cpp
 *
 * @code{.cpp}
 *     string s;
 *     vector<int> man(manacher(s)), longest(longest_from_index(man));
 *     // or
 *     vector<int> arr;
 *     vector<int> man(manacher(arr)), longest(longest_from_index(man));
 * @endcode
 *
 * @param man manacher array
 * @returns longest where:
 *      - s.substr(i, i + longest[i]) is a palindrome
 *      - s.substr(i, i + j) is not a palindrome, if j > longest[i]
 * @time O(n)
 * @space an O(n) vector is allocated and returned
 */
vector<int> longest_from_index(const vector<int>& man) {
    int n = (ssize(man) + 1) / 2;
    vector longest(n, 1);
    for (int i = n - 2; i >= 0; i--) {
        longest[i] = min(longest[i + 1] + 2, n - i);
        while (!is_pal(man, i, i + longest[i])) longest[i]--;
    }
    return longest;
}
