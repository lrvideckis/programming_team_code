typedef __int128 ll;

ll mulMod(ll x, ll y, ll p) {
	return (x*y)%p;
}

ll powMod(ll x, ll k, ll m) {
	if (k == 0) return 1;
	if ((k & 1)) return mulMod(x,powMod(x, k-1, m), m);
	else return powMod(mulMod(x,x,m), k/2, m);
}

bool suspect(ll a, ll s, ll d, ll n) {
	ll x = powMod(a, d, n);
	if (x == 1) return true;
	for (ll r = 0; r < s; ++r) {
		if (x == n - 1) return true;
		x = mulMod(x, x, n);
	}
	return false;
}

bool isPrime(ll n) {
	if (n <= 1 || (n > 2 && n % 2 == 0)) return false;
	ll test[] = {2,3,5,7,11,13,17,19,23,-1};
	ll d = n - 1, s = 0;
	while (d % 2 == 0) ++s, d /= 2;
	for (ll i = 0; test[i] < n && test[i] != -1; ++i)
		if (!suspect(test[i], s, d, n)) return false;
	return true;
}

ll pollard_rho(ll n, ll seed) { // always call factorize
	ll x, y;
	x = y = rand() % (n - 1) + 1;
	ll head = 1, tail = 2;
	while (true) {
		x = mulMod(x, x, n);
		x = (x + seed) % n;
		if (x == y) return n;
		ll d = __gcd(max(x - y, y - x), n);
		if (1 < d && d < n) return d;
		if (++head == tail) y = x, tail <<= 1;
	}
}

void factorize(ll n, vector<ll> &divisor) { // pollard-rho factorization
	if (n == 1) return;
	if (isPrime(n)) divisor.push_back(n);
	else {
	ll d = n;
	while (d >= n) d = pollard_rho(n, rand() % (n - 1) + 1);
		factorize(n / d, divisor);
		factorize(d, divisor);
	}
}
