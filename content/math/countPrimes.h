#pragma once

//status: not tested

const int MAX =1000005;
bool prime[MAX];
int prec[MAX];
vector<int> P;

ll rec(ll N, int K) {
	if (N <= 1 || K < 0) return 0;
	if (N <= P[K]) return N-1;
	if (N < MAX && ll(P[K])*P[K] > N) return N-1 - prec[N] + prec[P[K]];
	const int LIM = 250;
	static int memo[LIM*LIM][LIM];
	bool ok = N < LIM*LIM;
	if (ok && memo[N][K]) return memo[N][K];
	ll ret = N/P[K] - rec(N/P[K], K-1) + rec(N, K-1);
	if (ok) memo[N][K] = ret;
	return ret;
}

// init_count_primes();
// count_primes(x);
// Time complexity: Around O(N ^ 0.75)
// Constants to configure:
// - MAX is the maximum value of sqrt(N) + 2
// increase MAX to increase time efficiency
ll count_primes(ll N) {
	if (N < MAX) return prec[N];
	int K = prec[(int)sqrt(N) + 1];
	return N-1 - rec(N, K) + prec[P[K]];
}

void init_count_primes() {
	prime[2] = true;
	for (int i = 3; i < MAX; i += 2) prime[i] = true;
	for (int i = 3; i*i < MAX; i += 2)
		if (prime[i])
			for (int j = i*i; j < MAX; j += i+i)
				prime[j] = false;
	for(int i = 0; i < MAX; ++i) if (prime[i]) P.push_back(i);
	for(int i = 1; i < MAX; ++i) prec[i] = prec[i-1] + prime[i];
}
