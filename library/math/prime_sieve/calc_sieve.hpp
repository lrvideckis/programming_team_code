/** @file */
#pragma once
const int N = 1001;
int sieve[N];
/**
 * @time O(n * log(log n))
 * @space O(n) for `sieve` vector
 */
void calc_sieve() {
    iota(begin(sieve), end(sieve), 0);
    for (int i = 2; i * i < N; i++)
        if (sieve[i] == i)
            for (int j = i * i; j < N; j += i)
                sieve[j] = min(sieve[j], i);
}
