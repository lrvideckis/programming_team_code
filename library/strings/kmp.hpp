#pragma once
/**
 * @file
 * @brief Knuth Morris Pratt
 * @code{.cpp}
 *     string s;
 *     KMP kmp_s(s);
 *     vector<int> a;
 *     KMP kmp_a(a);
 * @endcode
 *
 * @trick KMP doubling trick: to check if 2 arrays are rotationally equivalent:
 * run kmp with one array as the needle and the other array doubled (excluding
 * the first & last characters) as the haystack or just use kactl's min
 * rotation code
 *
 * @memory O(|needle|)
 */
#include "prefix_function.hpp"
//NOLINTNEXTLINE(readability-identifier-naming)
template <typename T> struct KMP {
	T needle;
	vector<int> pi;
	KMP(const T& a_needle) : needle(a_needle), pi(prefix_function(needle)) {} ///< @time O(|needle|)
	/**
	 * @brief Matches `needle` into `haystack`.
	 *
	 * Let haystack = "bananas",
	 * needle = "ana". Then we find 2 matches:
	 * @code{.unparsed}
	 *     bananas
	 *     _ana___
	 *     ___ana_
	 *     0123456 (indexes)
	 * @endcode
	 * and `find` will return {1, 3} - the indexes in haystack where each match
	 * starts.
	 *
	 * @trick To check if there exists some match: pass in `0` for `all` and
	 * `find` will only return the first match: {1}. Useful for checking if
	 * there exists some match: `ssize(kmp.find("some string", 0)) > 0`.
	 *
	 * @time O(|needle| + |haystack|)
	 */
	vector<int> find(const T& haystack, bool all = 1) const {
		vector<int> matches;
		for (int i = 0, j = 0; i < ssize(haystack); i++) {
			while (j > 0 && needle[j] != haystack[i])
				j = pi[j - 1];
			if (needle[j] == haystack[i])
				j++;
			if (j == ssize(needle)) {
				matches.push_back(i - ssize(needle) + 1);
				if (!all)
					return matches;
				j = pi[j - 1];
			}
		}
		return matches;
	}
};
