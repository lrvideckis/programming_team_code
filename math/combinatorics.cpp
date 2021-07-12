//returns x such that x*a == 1 (mod b)
//x only exists if gcd(a, b) == 1
ll modInverse(int a, int b){
	return 1<a ? b - modInverse(b%a,a)*b/a : 1;
}

//returns a^pw % mod
ll fastPow(int a, int pw, int mod) {
 int res = 1;
	a %= mod;
	while(pw > 0) {
		if(pw & 1) res = (res*a)%mod;
		a = (a*a)%mod;
		pw >>= 1;
	}
	return res;
}

struct NchooseK {
	int range, mod;
	vector<ll> fact,ifact;

	NchooseK(int currMod) {
		this->mod = currMod;
		range = min((int)1e6+3,currMod);
		fact.resize(range+1);
		ifact.resize(range+1);
		calcFacts();
	}

	void calcFacts() {
		fact[0] = 1;
		for(int i = 1; i <= range; ++i) {
			fact[i] = (1LL*fact[i-1]*i)%this->mod;
		}
		ifact[range] = fastPow(fact[range], this->mod-2, this->mod);
		for(int i = range-1; i >= 0; --i) {
			ifact[i] = (1LL*ifact[i+1]*(i+1))%this->mod;
		}
	}

	//helper function for calcChoose
 int modFact(int n, int &e) const {
		if(n <= 1) return 1;
	 int res = modFact(n/this->mod, e);
		e += n/this->mod;
		if ((n/this->mod)%2 == 1) return res*(fact[n%this->mod]*(this->mod-1)%this->mod)%this->mod;
		return res*fact[n%this->mod]%this->mod;
	}

	//n choose k with n >= mod
	//***use prime moduli***
 int calcChoose(int n, int k) const {
	 int e1 = 0, e2 = 0, e3 = 0;
	 int a1 = modFact(n, e1);
	 int a2 = modFact(k, e2);
	 int a3 = modFact(n-k, e3);
		if (e1-e2-e3 > 0) return 0;
		return (a1*fastPow (a2*a3%this->mod, this->mod-2, this->mod)%this->mod);
	}

	//classic n choose k
	//***use prime moduli***
 int choose(int n, int k) const {
		if(k < 0 || k > n || n < 0) return 0;
		return ((1LL*fact[n]*ifact[k])%this->mod * 1LL*ifact[n-k])%this->mod;
	}

	//lucas theorem to calculate n choose k in O(log(k))
	//***use prime moduli***
	//***can only use with: prime moduli < 1e6***
 int chooseLucas(int n, int k) const {
		if(k < 0 || k > n || n < 0) return 0;
		if(k == 0) return 1;
		int ni = n % this->mod;
		int ki = k % this->mod;
		return (this->chooseLucas(n/this->mod, k/this->mod) * this->choose(ni,ki)) % this->mod;
	}

	//bars and stars problem: given n objects, each with an endless supply,
	//this returns the number of ways to choose k of them.
 int multiChoose(int n, int k) const {
		return chooseLucas(n+k-1, n-1);
	}
};
