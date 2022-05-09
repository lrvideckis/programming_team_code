//usage:
//	string s;
//	Hash h(s);
//or
//	vector<int> arr;
//	Hash h(arr);
//
//	works for -2e9 - 1000 <= arr[i] <= 2e9 + 1000
//
//status: tested on random inputs, on https://judge.yosupo.jp/problem/zalgorithm, and on https://judge.yosupo.jp/problem/enumerate_palindromes

#pragma once

#include "../misc/random.h"

const unsigned mod = 4294967087; // largest prime p < UINT_MAX such that (p-1)/2 is also prime
const int mx = 2e9 + 1000;
const vector<unsigned> bases {
	getRand<unsigned>(2u * mx + 2, mod - 1),
	getRand<unsigned>(2u * mx + 2, mod - 1),
	getRand<unsigned>(2u * mx + 2, mod - 1)
};

template <class T>
struct Hash {
	vector<vector<unsigned>> prefix, powB;

	Hash(const T& s) :
		prefix(bases.size(), vector<unsigned> (s.size() + 1, 0)),
		powB(bases.size(), vector<unsigned> (s.size() + 1, 1)) {
		for (auto val : s) assert(-mx <= val && val <= mx);
		for (int i = 0; i < (int) bases.size(); i++) {
			for (int j = 0; j < (int) s.size(); j++) {
				powB[i][j + 1] = 1ULL * powB[i][j] * bases[i] % mod;
				prefix[i][j + 1] = (1ULL * bases[i] * prefix[i][j] + s[j] + mx + 1) % mod;
			}
		}
	}

	void debugCollisionProbability() const {
		// (1 - (str_len / mod) ^ #bases) ^ #comparisons
		auto getProb = [&](long long num_comparisons) -> double {
			return pow(1 - pow(powB[0].size() / double(mod), bases.size()), num_comparisons);
		};
		long long num_comparisons = 1e5;
		cerr << fixed << setprecision(10) << "Probability of **no** collisions when doing "
		     << num_comparisons << " comparisons is ~ " << getProb(num_comparisons) << endl;
		long long k = 1e5;
		cerr << fixed << setprecision(10) << "Probability that " << k << " unique strings have "
		     << k << " unique hashes (if storing hashes in a std::set) is "
		     << getProb(k * (k - 1) / 2) << endl;
	}

	//returns hashes of substring/subarray [L,R] inclusive, one hash per base
	vector<unsigned> operator()(int L, int R) const {
		assert(0 <= L && L <= R && R + 1 < (int) prefix[0].size());
		vector<unsigned> res(bases.size());
		for (int i = 0; i < (int) bases.size(); i++) {
			long long x = 1LL * prefix[i][R + 1] + mod - 1ULL * prefix[i][L] * powB[i][R - L + 1] % mod;
			res[i] = x >= mod ? x - mod : x;
		}
		return res;
	}
};
