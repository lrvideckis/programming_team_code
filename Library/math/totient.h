#pragma once

//status: tested on n in range [1, 800]

//  Euler's totient function counts the positive integers
//  up to a given integer n that are relatively prime to n.

//To improve, use Pollard-rho to find prime factors

int totient(int n) {
	assert(n >= 1);
	int result = n;
	for (int i = 2, tempN = n; i * i <= tempN; i++) {
		if (n % i == 0) {
			while (n % i == 0) n /= i;
			result -= result / i;
		}
	}
	if (n > 1) result -= result / n;
	return result;
}
