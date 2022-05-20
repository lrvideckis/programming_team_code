#pragma once

//usage:
//	string needle;
//	...
//	KMP_Match kmp(needle);
//or
//	vector<int> needle;
//	...
//	KMP_Match kmp(needle);
//
//status: tested on random inputs

//kmp-doubling-trick: to check if 2 arrays are rotationally equivalent: run kmp
//with one array as the needle and the other array doubled as the haystack
//or just use kactl's min rotation code
template <class T>
struct KMP_Match {
public:
	KMP_Match(const T& needle_) : prefixFunction(needle_.size() + 1, 0), needle(needle_) {
		for (int i = 1, p = 0; i < (int) needle.size(); i++) {
			update(needle[i], p);
			prefixFunction[i + 1] = p;
		}
	};

	// if haystack = "bananas"
	// needle = "ana"
	//
	// then we find 2 matches:
	// bananas
	// _ana___
	// ___ana_
	// 0123456 (indexes)
	// and KMP_Match::find returns {1,3} - the indexes in kaystack where
	// each match starts.
	//
	// You can also pass in false for "all" and KMP_Match::find will only
	// return the first match: {1}. Useful for checking if there exists
	// some match:
	//
	// KMP_Match::find(<haystack>,false).size() > 0
	vector<int> find(const T& haystack, bool all = true) const {
		vector<int> matches;
		for (int i = 0, p = 0; i < (int) haystack.size(); i++) {
			update(haystack[i], p);
			if (p == (int) needle.size()) {
				matches.push_back(i - (int) needle.size() + 1);
				if (!all) return matches;
				p = prefixFunction[p];
			}
		}
		return matches;
	}
private:
	void update(char val, int& p) const {
		while (p && val != needle[p]) p = prefixFunction[p];
		if (val == needle[p]) p++;
	}
	vector<int> prefixFunction;
	T needle;
};
