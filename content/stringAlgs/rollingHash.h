#pragma once

//usage:
//	Hash<string> h(s);
//or
//	Hash<vector<int>> h(arr);
//	here, for negatives, compress values to {1,2,...,n} and make sure `base` is > n
template <class T>
struct Hash {
	//`base` should be reletavely prime with all mods and *strictly* larger than max element
	//ideally would be random to avoid getting hacked
	const int base = 1e9+5;
	vector<int> mods;
	vector<vector<int>> prefix, powB;

	//primes: 10^9 + {7,9,21,33,87}
	Hash(const T& s, vector<int> currMods = {(int)1e9+7, (int)1e9+9, (int)1e9+21, (int)1e9+33, (int)1e9+87}) :
		mods(currMods),
		prefix(currMods.size(), vector<int>(s.size())),
		powB(currMods.size(), vector<int>(s.size(), 1)) {
		//negatives may cause trivial collisions, when s[i]%mod = s[j]%mod, but s[i] != s[j]
		//0's cause trivial collisions: "0" and "00" both hash to 0
		for(auto val : s) assert(val > 0);
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

	//returns hashes of substring [L,R] inclusive, one hash per mod in the order mods were given in the constructor
	vector<int> getHashes(int L, int R) const {
		assert(L <= R);
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
