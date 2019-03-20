const ll mod = 1e9+7;

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

//Faulhaber'the sum of the k-th powers of the first n positive integers
//1^k + 2^k + 3^k + 4^k + ... + n^k
//O(k*log(k))
int faulhaber(long long n, int k){
    vector<ll> sum(k+5, 0);
    for(ll i=1;i<=k+2;i++) {
        sum[i]=sum[i-1]+fastPow(i,k, mod);
        if(sum[i] >= mod) sum[i] -= mod;
    }
    if(n<=k+2) return sum[n];
    ll t = 1;
    vector<ll> fac(k+5, 1);
    for(ll i=1;i<=k+2;i++) {
        t=(n-i)*t%mod;
        fac[i]=fac[i-1]*i%mod;
    }
    ll ans = 0;
    for(ll i=1;i<=k+2;i++) {
        ll t1=fastPow(fac[i-1]*fac[k-i+2]%mod,mod-2, mod);
        ll t2=fastPow(n-i,mod-2, mod);
        if((k-i+2)&1)t1=-t1;
        ans+=sum[i]*t%mod*t1%mod*t2%mod;
        if(ans >= mod) ans -= mod;
        //if(ans < 0) ans += mod;
        //assert(0 <= ans && ans < mod);
    }
    if(ans < 0) ans += mod;
    return ans;
}
