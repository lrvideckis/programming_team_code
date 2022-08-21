#pragma once
//a_prime[val] = some random prime factor of `val`
//
//to check if `val` is prime:
//	if (a_prime[val] == val)
//
//to get all prime factors of a number `val` in O(log(val)):
//	while (val > 1) {
//		int p = a_prime[val];
//		//p is some prime factor of val
//		val /= p;
//	}
const int N = 1e6 + 10;
int a_prime[N];
void calc_seive() {
	iota(a_prime, a_prime + N, 0);
	for (int i = 2; i * i < N; i++)
		if (a_prime[i] == i)
			for (int j = i * i; j < N; j += i)
				a_prime[j] = i;
}
