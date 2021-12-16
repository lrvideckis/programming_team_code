#pragma once

//returns a^pw % mod in O(log(pw))
ll fastPow(ll a, ll pw, int mod) {
	ll res = 1;
	a %= mod;
	while(pw > 0) {
		if(pw & 1) res = (res*a)%mod;
		a = (a*a)%mod;
		pw >>= 1;
	}
	return res;
}
