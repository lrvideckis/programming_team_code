ll mulMod(ll x, ll y, ll p) {
    if (y == 0) return 0;
    if (x < 1000111000111000111ll / y) return x * y % p;
    ll mid = mulMod((x+x)%p, y>>1ll, p);
    if (y & 1) return (mid + x) % p;
    else return mid;
}
ll powMod(ll x, ll k, ll m) {
    if (k == 0) return 1;
    if ((k & 1)) return mulMod(x,powMod(x, k-1, m), m);
    else return powMod(mulMod(x,x,m), k/2, m);
}
bool suspect(ll a, ll s, ll d, ll n) {
    ll x = powMod(a, d, n);
    if (x == 1) return true;
    for (int r = 0; r < s; ++r) {
        if (x == n - 1) return true;
        x = mulMod(x, x, n);
    }
    return false;
}
// {2,7,61,-1}                      is for n < 4759123141 (= 2^32)
// {2,3,5,7,11,13,17,19,23,-1} is for n < 10^15 (at least)
bool isPrime(ll n) {
    if (n <= 1 || (n > 2 && n % 2 == 0)) return false;
    ll test[] = {2,3,5,7,11,13,17,19,23,-1};
    ll d = n - 1, s = 0;
    while (d % 2 == 0) ++s, d /= 2;
    for (int i = 0; test[i] < n && test[i] != -1; ++i)
        if (!suspect(test[i], s, d, n)) return false;
    return true;
}
// Killer prime: 5555555557ll (fail when not used mulMod)

ll pollard_rho(ll n, ll seed) { // always call factorize
  ll x, y;
  x = y = rand() % (n - 1) + 1;
  int head = 1, tail = 2;
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
