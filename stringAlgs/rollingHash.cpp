struct Hash {
	const int base = 257;
	vector<int> mods;
	vector<vector<int>> prefix, powB;

	Hash(const string &s, const vector<int> &currMods) :
		mods(currMods),
		prefix(currMods.size(), vector<int>(s.size())),
		powB(currMods.size(), vector<int>(s.size(), 1)) {
			for(int i = 0; i < (int)mods.size(); i++) {
				for(int j = 1; j < (int)s.size(); j++) {
					powB[i][j] = 1LL * powB[i][j-1] * base % mods[i];
				}
				int sum = 0;
				for(int j = 0; j < (int)s.size(); j++) {
					sum = (1LL * base * sum + s[j]) % mods[i];
					prefix[i][j] = sum;
				}
			}
		}


	//returns hashes of substring [L,R] inclusive
	vector<int> getHashes(int L, int R) const {
		vector<int> allHashes;
		for(int i = 0; i < (int)mods.size(); i++) {
			int currHash = prefix[i][R];
			if(L) {
				currHash -= 1LL * prefix[i][L-1] * powB[i][R-L+1] % mods[i];
				if(currHash < 0) currHash += mods[i];
			}
			allHashes.push_back(currHash);
		}
		return allHashes;
	}
};
