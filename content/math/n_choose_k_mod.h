#pragma once

//status: tested on random inputs

#include "exp_mod.h"

// usage:
//     NchooseK nk(n, 1e9+7) to use `choose`
// or:
//     NchooseK nk(mod-1, mod) to use `chooseWithLucasTheorem`
struct NchooseK {
	// `maxFact` is the largest factorial we calculate, so don't call choose() with n > maxFact
	NchooseK(int maxFact, int currMod) : mod(currMod), fact(maxFact+1, 1), invFact(maxFact+1) {
		//this implimentation of doesn't work if maxFact >= mod because n! % mod = 0 when n >= mod. So `invFact` array will be all 0's
		assert(maxFact < mod);
		//assert mod is prime. mod is intended to fit inside an int so that
		//multiplications fit in a longlong before being modded down. So this
		//will take sqrt(2^31) time
		assert(mod >= 2);
		for(int i = 2; i * i <= mod; i++) {
			assert(mod % i);
		}
		for(int i = 1; i <= maxFact; i++) {
			fact[i] = 1LL * fact[i-1] * i % mod;
		}
		invFact[maxFact] = fastPow(fact[maxFact], mod-2, mod);
		for(int i = maxFact-1; i >= 0; i--) {
			invFact[i] = 1LL * invFact[i+1] * (i+1) % mod;
		}
	}

	//classic n choose k
	//doesn't work with n >= mod
	int choose(int n, int k) const {
		if(k < 0 || k > n) return 0;
		//now we know 0 <= k <= n so 0 <= n
		return 1LL * fact[n] * invFact[k] % mod * invFact[n-k] % mod;
	}

	//lucas theorem to calculate n choose k in O(log(k))
	//need to calculate all factorials in range [0,mod), so O(mod) time&space, so need smallish mod (< 1e6 maybe)
	//handles n >= mod correctly
	int chooseWithLucasTheorem(ll n, ll k) const {
		if(k < 0 || k > n) return 0;
		if(k == 0 || k == n) return 1;
		return 1LL * chooseWithLucasTheorem(n/mod, k/mod) * choose(n%mod, k%mod) % mod;
	}

	//returns inverse of n in O(1)
	int inv(int n) const {
		assert(1 <= n);//don't divide by 0 :)
		return 1LL * fact[n-1] * invFact[n] % mod;
	}

	int mod;
	vector<int> fact, invFact;
};
