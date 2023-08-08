/** @file */
#pragma once
const int n = 1001;
int sieve[n];
/**
 * @time O(n * log(log n))
 * @space O(n) for `sieve` vector
 */
void calc_sieve() {
    iota(begin(sieve), end(sieve), 0);
    for (int i = 2; i * i < n; i++)
        if (sieve[i] == i)
            for (int j = i * i; j < n; j += i)
                sieve[j] = min(sieve[j], i);
}
