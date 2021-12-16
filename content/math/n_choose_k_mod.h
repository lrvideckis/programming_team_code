#pragma once

//returns x such that x*val%mod == 1
//x only exists if gcd(val, mod) == 1
//source: https://codeforces.com/blog/entry/23365
ll modInverse(ll val, ll mod) {
	return 1<val ? mod - modInverse(mod%val,val)*mod/val : 1;
}

struct NchooseK {
	// maxFact is the largest factorial we calculate, so don't call choose() with n > maxFact
	// set maxFact = (currMod-1) to use chooseWithLucasTheorem
	NchooseK(int maxFact, int currMod) : mod(currMod), fact(maxFact+1, 1), invFact(maxFact+1) {
		//inverse factorial calculation won't work if maxFact >= currMod
		assert(maxFact < currMod);
		//assert mod is prime
		assert(currMod >= 2);
		for(int i = 2; i * i <= currMod; i++) {
			assert(currMod % i);
		}
		for(int i = 1; i <= maxFact; i++) {
			fact[i] = 1LL * fact[i-1] * i % mod;
		}
		invFact[maxFact] = modInverse(fact[maxFact], mod);
		for(int i = maxFact-1; i >= 0; i--) {
			invFact[i] = 1LL * invFact[i+1] * (i+1) % mod;
		}
	}

	//classic n choose k
	//doesn't work with n >= mod
	int choose(int n, int k) const {
		if(k < 0 || k > n) return 0;
		return 1LL * fact[n] * invFact[k] % mod * invFact[n-k] % mod;
	}

	//lucas theorem to calculate n choose k in O(log(k))
	//need to calculate all factorials in range [0,mod), so O(mod) time&space, so need smallish mod (< 1e6 maybe)
	//handles n >= mod correctly
	int chooseWithLucasTheorem(ll n, ll k) const {
		if(k < 0 || k > n) return 0;
		if(k == 0) return 1;
		return 1LL * chooseWithLucasTheorem(n/mod, k/mod) * choose(n%mod, k%mod) % mod;
	}

	//bars and stars problem: given n objects, each with an endless supply,
	//this returns the number of ways to choose k of them.
	int multiChoose(ll n, ll k) const {
		return chooseWithLucasTheorem(n+k-1, n-1);
	}

	int mod;
	vector<int> fact, invFact;
};
