/** @file */
#pragma once
const int mx_n = 1001;
int sieve[mx_n];
/**
 * @returns a list of all of the primes < mx_n
 * @time O(mx_n * log(log mx_n))
 * @space O(mx_n) for `sieve` vector
 */
vector<int> calc_sieve() {
    iota(begin(sieve), end(sieve), 0);
    vector<int> primes;
    for (int i = 2; i < mx_n; i++) {
        if (sieve[i] == i) {
            for (int prime : primes) {
                int prod = prime * i;
                if (prod >= mx_n || prime % i == 0)
                    break;
                sieve[prod] = i;
            }
            primes.push_back(i);
        }
    }
    return primes;
}
