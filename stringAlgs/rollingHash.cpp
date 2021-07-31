struct Hash {
	//for least collisions, base should be a prime > the alphabet size
	const int base = 33;
	int mod;
	vector<int> prefix, powB;
	Hash(const string &s, int currMod) : mod(currMod), prefix(s.size()), powB(s.size(), 1) {
		for(int i = 1; i < (int)s.size(); i++) {
			powB[i] = 1LL * powB[i-1] * base % mod;
		}
		int sum = 0;
		for(int i = 0; i < (int)s.size(); i++) {
			sum = (1LL * base * sum + s[i]-'0') % mod;
			prefix[i] = sum;
		}
	}
	//returns hash of substring [i,j] inclusive
	int getHash(int i, int j) {
		int res = prefix[j];
		if(i-1 >= 0) {
			res -= 1LL * prefix[i-1] * powB[j-i+1] % mod;
			if(res < 0) res += mod;
		}
		return res;
	}
};
