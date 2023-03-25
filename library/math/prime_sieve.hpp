/** @file */
#pragma once
/**
 * @param val an integer
 * @param sieve prime sieve
 * @returns 1 iff val is prime
 * @time O(1)
 */
bool is_prime(int val, const vector<int>& sieve) {
	assert(val < ssize(sieve));
	return val >= 2 && sieve[val] == val;
}
/**
 * @param val an integer
 * @param sieve prime sieve
 * @returns all prime factors of val
 * @time O(log(val))
 */
vector<int> get_prime_factors(int val, const vector<int>& sieve) {
	assert(val < ssize(sieve));
	vector<int> factors;
	while (val > 1) {
		int p = sieve[val];
		factors.push_back(p);
		val /= p;
	}
	return factors;
}
/**
 * @param n size
 * @returns array `sieve` where `sieve[i]` = some prime factor of `i`.
 * @time O(n * log(logn))
 * @memory O(n)
 */
vector<int> get_sieve(int n) {
	vector<int> sieve(n);
	iota(sieve.begin(), sieve.end(), 0);
	for (int i = 2; i * i < n; i++)
		if (sieve[i] == i)
			for (int j = i * i; j < n; j += i)
				sieve[j] = min(sieve[j], i);
	return sieve;
}
