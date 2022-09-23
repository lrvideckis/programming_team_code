#pragma once
#include "binary_exponentiation_mod.hpp"
#include "totient.hpp"
//to calculate (base^pw)%mod with huge pw and non-prime mod:
//let t = totient(mod)
//if log2(mod) <= pw then (base^pw)%mod == (base^(t+(pw%t)))%mod
//source: https://cp-algorithms.com/algebra/phi-function.html#generalization
//
//returns base ^ (base ^ (base ^ ... )) % mod, where the height of the tower is pw
long long tetration(long long base, long long pw, long long mod) {
	if (mod == 1)
		return 0;
	if (base == 0)
		return (pw + 1) % 2 % mod;
	if (base == 1 || pw == 0)
		return 1;
	if (pw == 1)
		return base % mod;
	if (base == 2 && pw == 2)
		return 4 % mod;
	if (base == 2 && pw == 3)
		return 16 % mod;
	if (base == 3 && pw == 2)
		return 27 % mod;
	//need enough base cases such that the following is true
	//log2(mod) <= tetration(base, pw - 1) (before modding)
	int t = totient(int(mod));
	long long exp = tetration(base, pw - 1, t);
	return bin_exp(base, exp + t, mod);
}
