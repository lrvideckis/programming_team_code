#pragma once
//mobius[i] = 0 iff there exists a prime p s.t. i%(p^2)=0
//mobius[i] = -1 iff i has an odd number of distinct prime factors
//mobius[i] = 1 iff i has an even number of distinct prime factors
const int MX_N = 1e6 + 10;
int mobius[MX_N];
void calc_mobius() {
	mobius[1] = 1;
	for (int i = 1; i < MX_N; i++)
		for (int j = i + i; j < MX_N; j += i)
			mobius[j] -= mobius[i];
}
