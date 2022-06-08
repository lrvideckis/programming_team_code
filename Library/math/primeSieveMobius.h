#pragma once
//status: not tested
//mobius[i] = 0 iff there exists a prime p s.t. i%(p^2)=0
//mobius[i] = -1 iff i has an odd number of distinct prime factors
//mobius[i] = 1 iff i has an even number of distinct prime factors
const int N = 2e6 + 10;
int mobius[N];
void calcMobius() {
	mobius[1] = 1;
	for (int i = 1; i < N; i++)
		for (int j = i + i; j < N; j += i)
			mobius[j] -= mobius[i];
}
//aPrime[val] = some random prime factor of `val`
//to get all prime factors of a number `val`:
//	while(val > 1) {
//		int p = aPrime[val];
//		//p is some prime factor of val
//		val /= p;
//	}
int aPrime[N];
void calcSeive() {
	iota(aPrime, aPrime + N, 0);
	for (int i = 2; i * i < N; i++)
		if (aPrime[i] == i)
			for (int j = i * i; j < N; j += i)
				aPrime[j] = i;
}
