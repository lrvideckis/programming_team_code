#pragma once
//library checker tests: https://judge.yosupo.jp/problem/system_of_linear_equations, https://judge.yosupo.jp/problem/binomial_coefficient, https://judge.yosupo.jp/problem/matrix_det
//stress tests: tests/stress-tests/math/exp_mod.cpp


//returns (base^pw)%mod in O(log(pw)), but returns 1 for 0^0


//What if base doesn't fit in long long?
//Since (base^pw)%mod == ((base%mod)%pw)%mod we can calculate base under mod of `mod`


//What if pw doesn't fit in long long?

//case 1: mod is prime
//(base^pw)%mod == (base^(pw%(mod-1)))%mod (from Fermat's little theorem)
//so calculate pw under mod of `mod-1`

//case 2: non-prime mod
//let t = totient(mod)
//if pw >= log2(mod) then (base^pw)%mod == (base^(t+(pw%t)))%mod (proof https://cp-algorithms.com/algebra/phi-function.html#generalization)
//so calculate pw under mod of `t`

int fastPow(long long base, long long pw, int mod) {
	assert(0 <= pw && 0 <= base && 1 <= mod);
	int res = 1;
	base %= mod;
	while (pw > 0) {
		if (pw & 1) res = res * base % mod;
		base = base * base % mod;
		pw >>= 1;
	}
	return res;
}
