#pragma once

//usage:
//	Hash<string> h(s);
//or
//	Hash<vector<int>> h(arr);
//	assumes 0 < arr[i] < 1e9+5 = `base`
//	here, for negatives or longlongs, compress values to {1,2,...,n} and make sure `base` is > n
//
//status: tested on random inputs, and on https://judge.yosupo.jp/problem/zalgorithm
template <class T>
struct Hash {
	//`base` should be relatively prime with all mods and *strictly* larger than max element
	//larger/smaller `base` *doesn't* change collision odds
	//ideally `base` would be random to avoid getting hacked
	const int base = 1e9 + 5;
	//From C.R.T., this is the same as having a single mod = product of `mods`
	//probability of collision = 1/mod_product
	//probability that k unique strings have k unique hashes = (1/mod_product)^k * (mod_product permute k) from birthday paradox
	const vector<int> mods = { (int) 1e9 + 7, (int) 1e9 + 9, (int) 1e9 + 21, (int) 1e9 + 33, (int) 1e9 + 87};
	vector<vector<int>> prefix, powB;

	Hash(const T& s) :
		prefix(mods.size(), vector<int> (s.size() + 1, 0)),
		powB(mods.size(), vector<int> (s.size() + 1, 1)) {
		//negatives may cause trivial collisions, when s[i]%mod = s[j]%mod, but s[i] != s[j]
		//0's cause trivial collisions: "0" and "00" both hash to 0
		for (auto val : s) assert(0 < val && val < base);
		for (int i = 0; i < (int) mods.size(); i++) {
			for (int j = 0; j < (int) s.size(); j++) {
				powB[i][j + 1] = 1LL * powB[i][j] * base % mods[i];
				prefix[i][j + 1] = (1LL * base * prefix[i][j] + s[j]) % mods[i];
			}
		}
	}

	//returns hashes of substring/subarray [L,R] inclusive, one hash per mod
	vector<int> getHashes(int L, int R) const {
		assert(0 <= L && L <= R && R + 1 < (int) prefix[0].size());
		vector<int> res(mods.size());
		for (int i = 0; i < (int) mods.size(); i++) {
			res[i] = prefix[i][R + 1] - 1LL * prefix[i][L] * powB[i][R - L + 1] % mods[i];
			if (res[i] < 0) res[i] += mods[i];
		}
		return res;
	}
};
