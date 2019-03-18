ll fastPow(ll a, ll pw, ll mod) {
	ll res = 1;
	while(pw) {
		if(pw & 1) res = (res*a)%mod; 
		a = (a*a)%mod;
		pw >>= 1;
	}
	return res;
}
