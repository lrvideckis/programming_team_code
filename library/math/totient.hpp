#pragma once
//Euler's totient function counts the positive integers
//up to a given integer n that are relatively prime to n.
//
//To improve, pre-calc prime factors or use Pollard-rho to find prime factors.
int totient(int n) {
	int RES = n;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			while (n % i == 0) n /= i;
			RES -= RES / i;
		}
	}
	if (n > 1) RES -= RES / n;
	return RES;
}
