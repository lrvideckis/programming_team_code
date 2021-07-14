struct KMP_Match {
	public:
		KMP_Match(const string &needle_) : prefixFunction(needle_.size()+1), needle(needle_) {
			int i = 0, j = -1;
			prefixFunction[i] = j;
			while(i < (int)needle.size()) {
				while(j >= 0 && needle[i] != needle[j]) j = prefixFunction[j];
				i++, j++;
				prefixFunction[i] = j;
			}
		};

		// if haystack = "bananas"
		// needle = "ana"
		//
		// then we find 2 matches (note they can overlap):
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
			int m = 0, i = 0;
			vector<int> matches;
			while(m + i < (int)haystack.size()) {
				if(needle[i] == haystack[m+i]) {
					if(i+1 == (int)needle.size()) {
						matches.push_back(m);
						if(!all) return matches;
						m = m + i - prefixFunction[i];
						i = prefixFunction[i];
					}
					i++;
				} else {
					if(prefixFunction[i] != -1) {
						m = m + i - prefixFunction[i];
						i = prefixFunction[i];
					} else {
						i = 0;
						m++;
					}
				}
			}
			return matches;
		}
	private:
		vector<int> prefixFunction;
		string needle;
};

int fail[1000005];

// Checks if two arrays are rotationally equvalent
bool KMPints(vector<ll> a, vector<ll> b){
	for(int i = 0; i < (int)a.size(); i++) {
		b.push_back(b[i]);
	}
	int p = 0;
	for(int i = 1; i < (int)a.size(); i++) {
		while(p && a[i] != a[p]) p = fail[p];
		if(a[i] == a[p]) p++;
		fail[i + 1] = p;
	}
	p = 0;
	for(auto &i : b) {
		while(p && i != a[p]) p = fail[p];
		if(i == a[p]) p++;
		if(p == (int)a.size()) return true;
	}
	return false;
}
