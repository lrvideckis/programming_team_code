#pragma once
//mnemonic: Knuth Morris Pratt
#include "prefix_function.h"
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
//NOLINTNEXTLINE(readability-identifier-naming)
template <class T> struct KMP {
	KMP(const T& a_needle) : pi(prefix_function(a_needle)), needle(a_needle) {}
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
	// You can also pass in false for "all" and KMP::find will only
	// return the first match: {1}. Useful for checking if there exists
	// some match:
	//
	// KMP::find(<haystack>,false).size() > 0
	vector<int> find(const T& haystack, bool all = true) const {
		vector<int> matches;
		for (int i = 0, j = 0; i < (int)haystack.size(); i++) {
			while (j > 0 && needle[j] != haystack[i]) j = pi[j - 1];
			if (needle[j] == haystack[i]) j++;
			if (j == (int)needle.size()) {
				matches.push_back(i - (int)needle.size() + 1);
				if (!all) return matches;
				j = pi[j - 1];
			}
		}
		return matches;
	}
	vector<int> pi;//prefix function
	T needle;
};
