#pragma once
//returns (base^pw)%mod in O(log(pw)), but returns 1 for 0^0
//
//What if base doesn't fit in long long?
//Since (base^pw)%mod == ((base%mod)^pw)%mod we can calculate base under mod of `mod`
//
//What if pw doesn't fit in long long?
//assuming mod is prime:
//(base^pw)%mod == (base^(pw%(mod-1)))%mod (from Fermat's little theorem)
//so calculate pw under mod of `mod-1`
//note `mod-1` is not prime, so you need to be able to calculate `pw%(mod-1)` without division
long long bin_exp(long long base, long long pw, long long mod) {
	assert(0 <= pw && 0 <= base && 1 <= mod);
	long long res = 1;
	base %= mod;
	while (pw > 0) {
		if (pw & 1) res = res * base % mod;
		base = base * base % mod;
		pw >>= 1;
	}
	return res;
}
