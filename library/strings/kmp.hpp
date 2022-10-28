#pragma once
//mnemonic: Knuth Morris Pratt
#include "prefix_function.hpp"
//usage:
//	string needle;
//	...
//	KMP kmp(needle);
//or
//	vector<int> needle;
//	...
//	KMP kmp(needle);
//kmp doubling trick: to check if 2 arrays are rotationally equivalent: run kmp
//with one array as the needle and the other array doubled (excluding the first
//& last characters) as the haystack or just use kactl's min rotation code
//
// if haystack = "bananas"
// needle = "ana"
//
// then we find 2 matches:
// bananas
// _ana___
// ___ana_
// 0123456 (indexes)
// and KMP::find returns {1,3} - the indexes in haystack where
// each match starts.
//
// You can also pass in 0 for "all" and KMP::find will only
// return the first match: {1}. Useful for checking if there exists
// some match:
//
// ssize(KMP::find(<haystack>,0)) > 0
//NOLINTNEXTLINE(readability-identifier-naming)
template <typename T> struct KMP {
	T needle;
	vector<int> pi;
	KMP(const T& a_needle) : needle(a_needle), pi(prefix_function(needle)) {}
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
