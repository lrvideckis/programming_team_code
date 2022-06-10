#pragma once
//stress tests: tests/stress_tests/math/prime_sieve_mobius.cpp
//status: not tested
//mobius[i] = 0 iff there exists a prime p s.t. i%(p^2)=0
//mobius[i] = -1 iff i has an odd number of distinct prime factors
//mobius[i] = 1 iff i has an even number of distinct prime factors
const int sz = 2e6 + 10;
int mobius[sz];
void calc_mobius() {
	mobius[1] = 1;
	for (int i = 1; i < sz; i++)
		for (int j = i + i; j < sz; j += i)
			mobius[j] -= mobius[i];
}
//a_prime[val] = some random prime factor of `val`
//to get all prime factors of a number `val`:
//	while(val > 1) {
//		int p = a_prime[val];
//		//p is some prime factor of val
//		val /= p;
//	}
int a_prime[sz];
void calc_seive() {
	iota(a_prime, a_prime + sz, 0);
	for (int i = 2; i * i < sz; i++)
		if (a_prime[i] == i)
			for (int j = i * i; j < sz; j += i)
				a_prime[j] = i;
}
