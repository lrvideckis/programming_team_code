struct KMP_Match {
public:
	KMP_Match(const string &needle_) : prefixFunction(needle_.size()+1, 0), needle(needle_) {
		int p = 0;
		for(int i = 1; i < (int)needle.size(); i++) {
			while(p && needle[i] != needle[p]) p = prefixFunction[p];
			if(needle[i] == needle[p]) p++;
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
	vector<int> find(const string &haystack, bool all = true) {
		int p = 0;
		vector<int> matches;
		for(int i = 0; i < (int)haystack.size(); i++) {
			while(p && haystack[i] != needle[p]) p = prefixFunction[p];
			if(haystack[i] == needle[p]) p++;
			if(p == (int)needle.size()) {
				matches.push_back(i - (int)needle.size() + 1);
				if(!all) return matches;
			}
		}
		return matches;
	}
private:
	vector<int> prefixFunction;
	string needle;
};
