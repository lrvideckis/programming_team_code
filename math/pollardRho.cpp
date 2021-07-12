typedef __int128 ll;

ll mulMod(int x, int y, int p) {
	return (x*y)%p;
}

ll powMod(int x, int k, int m) {
	if (k == 0) return 1;
	if ((k & 1)) return mulMod(x,powMod(x, k-1, m), m);
	else return powMod(mulMod(x,x,m), k/2, m);
}

bool suspect(int a, int s, int d, int n) {
 int x = powMod(a, d, n);
	if (x == 1) return true;
	for (int r = 0; r < s; ++r) {
		if (x == n - 1) return true;
		x = mulMod(x, x, n);
	}
	return false;
}

bool isPrime(int n) {
	if (n <= 1 || (n > 2 && n % 2 == 0)) return false;
 int test[] = {2,3,5,7,11,13,17,19,23,-1};
 int d = n - 1, s = 0;
	while (d % 2 == 0) ++s, d /= 2;
	for (int i = 0; test[i] < n && test[i] != -1; ++i)
		if (!suspect(test[i], s, d, n)) return false;
	return true;
}

ll pollard_rho(int n, int seed) { // always call factorize
 int x, y;
	x = y = rand() % (n - 1) + 1;
 int head = 1, tail = 2;
	while (true) {
		x = mulMod(x, x, n);
		x = (x + seed) % n;
		if (x == y) return n;
	 int d = __gcd(max(x - y, y - x), n);
		if (1 < d && d < n) return d;
		if (++head == tail) y = x, tail <<= 1;
	}
}

void factorize(int n, vector<ll> &divisor) { // pollard-rho factorization
	if (n == 1) return;
	if (isPrime(n)) divisor.push_back(n);
	else {
 int d = n;
	while (d >= n) d = pollard_rho(n, rand() % (n - 1) + 1);
		factorize(n / d, divisor);
		factorize(d, divisor);
	}
}
