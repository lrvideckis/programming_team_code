#pragma once
#include "prefix_function.hpp"
/**
 * @brief Knuth Morris Pratt
 * @code{.cpp}
 *     string s;
 *     KMP kmp(s);
 *     vector<int> a;
 *     KMP kmp(a);
 * @endcode
 * @trick KMP doubling trick: to check if 2 arrays are rotationally equivalent:
 *     run kmp with one array as the needle and the other array doubled
 *     (excluding the first & last characters) as the haystack or just use
 *     kactl's min rotation code.
 */
//NOLINTNEXTLINE(readability-identifier-naming)
template <typename T> struct KMP {
	T needle;
	vector<int> pi;
	/**
	 * @time O(|needle|)
	 * @memory O(|needle|)
	 */
	KMP(const T& a_needle) : needle(a_needle), pi(prefix_function(needle)) {}
	/**
	 * @brief Returns array `matches` where:
	 *     haystack.substr(matches[i], ssize(needle)) == needle
	 * @time O(|needle| + |haystack|)
	 */
	vector<int> find(const T& haystack) const {
		vector<int> matches;
		for (int i = 0, j = 0; i < ssize(haystack); i++) {
			while (j > 0 && needle[j] != haystack[i])
				j = pi[j - 1];
			if (needle[j] == haystack[i])
				j++;
			if (j == ssize(needle)) {
				matches.push_back(i - ssize(needle) + 1);
				j = pi[j - 1];
			}
		}
		return matches;
	}
};
