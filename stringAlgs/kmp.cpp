struct KMP_Match {
	public:
		KMP_Match(string pattern) : T(pattern.size()+1), pat(pattern) {
			int i = 0, j = -1;
			T[i] = j;
			while(i < (int)pat.size()) {
				while(j >= 0 && pat[i] != pat[j]) j = T[j];
				i++, j++;
				T[i] = j;
			}
		};
		vector<int> find(string txt, bool all = true) {
			int m = 0, i = 0;
			vector<int> matches;
			while(m + i < (int)txt.size()) {
				if(pat[i] == txt[m+i]) {
					if(i+1 == (int)pat.size()) {
						matches.push_back(m);
						if(!all) return matches;
						m = m + i - T[i];
						i = T[i];
					}
					i++;
				} else {
					if(T[i] != -1) {
						m = m + i - T[i];
						i = T[i];
					} else {
						i = 0;
						m++;
					}
				}
			}
			return matches;
		}
	private:
		vector<int> T;
		string pat;
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
