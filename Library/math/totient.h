#pragma once
//stress tests: tests/stress-tests/math/totient.cpp

//  Euler's totient function counts the positive integers
//  up to a given integer n that are relatively prime to n.

//To improve, use Pollard-rho to find prime factors

int totient(int n) {
	assert(n >= 1);
	int res = n;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			while (n % i == 0) n /= i;
			res -= res / i;
		}
	}
	if (n > 1) res -= res / n;
	return res;
}
