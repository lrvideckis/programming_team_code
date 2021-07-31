//returns x such that x*val%mod == 1
//x only exists if gcd(val, mod) == 1
ll modInverse(ll val, ll mod) {
	return 1<val ? mod - modInverse(mod%val,val)*mod/val : 1;
}

//returns a^pw % mod
ll fastPow(ll a, ll pw, ll mod) {
	ll res = 1;
	a %= mod;
	while(pw > 0) {
		if(pw & 1) res = (res*a)%mod;
		a = (a*a)%mod;
		pw >>= 1;
	}
	return res;
}

struct NchooseK {
	// maxFact is the largest factorial we calculate, so don't call choose() with n > maxFact
	// set maxFact = (currMod-1) to use chooseWithLucasTheorem
	NchooseK(int maxFact, int currMod) : mod(currMod), fact(maxFact+1, 1), invFact(maxFact+1) {
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
	//needs O(mod) memory, so need smallish mod (< 1e6 maybe)
	//handles n >= mod correctly
	int chooseWithLucasTheorem(ll n, ll k) const {
		if(k < 0 || k > n) return 0;
		if(k == 0) return 1;
		int ni = n % mod;
		int ki = k % mod;
		return 1LL * chooseWithLucasTheorem(n/mod, k/mod) * choose(ni,ki) % mod;
	}

	//bars and stars problem: given n objects, each with an endless supply,
	//this returns the number of ways to choose k of them.
	int multiChoose(ll n, ll k) const {
		return chooseWithLucasTheorem(n+k-1, n-1);
	}

	int mod;
	vector<int> fact, invFact;
};
