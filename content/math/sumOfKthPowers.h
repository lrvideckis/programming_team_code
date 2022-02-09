#pragma once

//status: not tested, but used on misc. problems

#define MAX 1000010
#define MOD 1000000007

//Faulhaber'the sum of the k-th powers of the first n positive integers
//1^k + 2^k + 3^k + 4^k + ... + n^k
//O(k*log(k))

//Usage: lgr::lagrange(n, k)

namespace lgr {
short factor[MAX];
int P[MAX], S[MAX], ar[MAX], inv[MAX];

inline int expo(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = (long long)res * a % MOD;
		a = (long long)a * a % MOD;
		b >>= 1;
	}
	return res;
}

int lagrange(long long n, int k) {
	if (!k) return (n % MOD);
	int i, j, x, res = 0;
	if (!inv[0]) {
		for (i = 2, x = 1; i < MAX; i++) x = (long long)x * i % MOD;
		inv[MAX - 1] = expo(x, MOD - 2);
		for (i = MAX - 2; i >= 0; i--) inv[i] = ((long long)inv[i + 1] * (i + 1)) % MOD;
	}
	k++;
	for (i = 0; i <= k; i++) factor[i] = 0;
	for (i = 4; i <= k; i += 2) factor[i] = 2;
	for (i = 3; (i * i) <= k; i += 2) {
		if (!factor[i]) {
			for (j = (i * i), x = i << 1; j <= k; j += x)
				factor[j] = i;
		}
	}
	for (ar[1] = 1, ar[0] = 0, i = 2; i <= k; i++) {
		if (!factor[i]) ar[i] = expo(i, k - 1);
		else ar[i] = ((long long)ar[factor[i]] * ar[i / factor[i]]) % MOD;
	}
	for (i = 1; i <= k; i++) {
		ar[i] += ar[i - 1];
		if (ar[i] >= MOD) ar[i] -= MOD;
	}
	if (n <= k) return ar[n];
	P[0] = 1, S[k] = 1;
	for (i = 1; i <= k; i++) P[i] = ((long long)P[i - 1] * ((n - i + 1) % MOD)) % MOD;
	for (i = k - 1; i >= 0; i--) S[i] = ((long long)S[i + 1] * ((n - i - 1) % MOD)) % MOD;
	for (i = 0; i <= k; i++) {
		x = (long long)ar[i] * P[i] % MOD * S[i] % MOD * inv[k - i] % MOD * inv[i] % MOD;
		if ((k - i) & 1) {
			res -= x;
			if (res < 0) res += MOD;
		} else {
			res += x;
			if (res >= MOD) res -= MOD;
		}
	}
	return (res % MOD);
}
}
