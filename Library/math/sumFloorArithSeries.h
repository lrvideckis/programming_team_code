#pragma once

//status: used on https://open.kattis.com/problems/itsamodmodmodmodworld

//computes:
//[p/q] + [2p/q] + [3p/q] + ... + [np/q]
//(p, q, n are natural numbers)
//[x] = floor(x)

long long cnt(long long p, long long q, long long n) {
	long long t = __gcd(p, q);
	p = p / t;
	q = q / t;
	long long s = 0;
	long long z = 1;
	while ((q > 0) && (n > 0)) {
		//(point A)
		t = p / q;
		s += z * t * n * (n + 1) / 2;
		p -= q * t;
		//(point B)
		t = n / q;
		s += z * p * t * (n + 1) - z * t * (p * q * t + p + q - 1) / 2;
		n -= q * t;
		//(point C)
		t = n * p / q;
		s += z * t * n;
		n = t;
		swap(p, q);
		z = -z;
	}
	return s;
}
