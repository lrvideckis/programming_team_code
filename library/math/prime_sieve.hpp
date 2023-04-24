/** @file */
#pragma once
const int N = 1001;
int sieve[N];
/**
 * @param val an integer
 * @returns 1 iff val is prime
 * @time O(1)
 */
bool is_prime(int val) {
    assert(val < N && sieve[1] == 1);
    return val >= 2 && sieve[val] == val;
}
/**
 * @param val an integer
 * @returns all prime factors of val (sorted)
 * @time O(log(val))
 */
vector<int> get_prime_factors(int val) {
    assert(val < N && sieve[1] == 1);
    vector<int> factors;
    while (val > 1) {
        int p = sieve[val];
        factors.push_back(p);
        val /= p;
    }
    return factors;
}
/**
 * @time O(n * log(logn))
 * @memory O(n)
 */
void init_sieve() {
    iota(begin(sieve), end(sieve), 0);
    for (int i = 2; i * i < N; i++)
        if (sieve[i] == i)
            for (int j = i * i; j < N; j += i)
                sieve[j] = min(sieve[j], i);
}