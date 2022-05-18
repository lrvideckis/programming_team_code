#pragma once

//status: not tested

//mobius[i] = 0 iff there exists a prime p s.t. i%(p^2)=0
//mobius[i] = -1 iff i has an odd number of distinct prime factors
//mobius[i] = 1 iff i has an even number of distinct prime factors
const int N = 2e6 + 10;
int mobius[N];
void calcMobius() {
	mobius[1] = 1;
	for (int i = 1; i < N; ++i) {
		for (int j = i + i; j < N; j += i)
			mobius[j] -= mobius[i];
	}
}

int minPrime[N];
void calcSeive() {
	fill(minPrime, minPrime + N, N);
	for (int i = N - 1; i >= 2; --i) {
		for (int j = i; j < N; j += i)
			minPrime[j] = i;
	}
}
