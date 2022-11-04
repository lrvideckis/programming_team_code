#pragma once
bool is_prime(int val, const vector<int>& sieve) {
	assert(val < ssize(sieve));
	return val >= 2 && sieve[val] == val;
}
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
 * Returns array `sieve` where `sieve[i]` = some prime factor of `i`.
 * @time O(n * log(logn))
 */
vector<int> get_sieve(int n) {
	vector<int> sieve(n);
	iota(sieve.begin(), sieve.end(), 0);
	for (int i = 2; i * i < n; i++)
		if (sieve[i] == i)
			for (int j = i * i; j < n; j += i)
				sieve[j] = i;
	return sieve;
}
