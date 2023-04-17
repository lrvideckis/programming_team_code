/** @file */
#pragma once
const int N = 1'000'005;
/**
 * mobius[i] = 0 iff there exists a prime p s.t. i%(p^2)=0
 * mobius[i] = -1 iff i has an odd number of distinct prime factors
 * mobius[i] = 1 iff i has an even number of distinct prime factors
 */
int mobius[N];
/**
 * @time O(n log n)
 */
void calc_mobius() {
    mobius[1] = 1;
    for (int i = 1; i < N; i++)
        for (int j = i + i; j < N; j += i)
            mobius[j] -= mobius[i];
}
