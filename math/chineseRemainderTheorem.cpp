inline ll LCM(ll a, ll b) {
	return a / __gcd(a, b) * b;
}

inline ll normalize(ll x, ll mod) {
	x %= mod;
	if (x < 0) x += mod;
	return x;
}

struct gcd_type { ll x, y, d; };

gcd_type ex_gcd(ll a, ll b) {
	if (b == 0) return {1, 0, a};
	gcd_type pom = ex_gcd(b, a % b);
	return {pom.y, pom.x - a / b * pom.y, pom.d};
}

// Chinese remainder theorem: find z such that
// z % mods[i] = vals[i] for all i.  Note that the solution is
// unique modulo M = lcm_i (mods[i]).  Return (z, M). On
// failure, M = -1. Note that we do not require the a[i]'s
// to be relatively prime.
pair<ll, ll> crt(const vector<int> &vals, const vector<int> &mods) {
	for(int i = 0; i < vals.size(); i++) {
		normalize(vals[i], mods[i]);
	}
	ll ans = vals[0];
	ll Lcm = mods[0];
	for(int i = 1; i < vals.size(); i++) {
		auto pom = ex_gcd(Lcm, mods[i]);
		int x1 = pom.x;
		int d = pom.d;
		if((vals[i] - ans) % d != 0) {
			return {0,-1};
		}
		ans = normalize(ans + x1 * (vals[i] - ans) / d % (mods[i] / d) * Lcm, Lcm * mods[i] / d);
		Lcm = LCM(Lcm, mods[i]); // you can save time by replacing above lcm * n[i] /d by lcm = lcm * n[i] / d
	}
	return {ans, Lcm};
}
