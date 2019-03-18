typedef long long ll;
typedef pair <ll, ll> ii;

ll md (ll x, ll mod) {
	x %= mod;
	if (x < 0)
		return x + mod;
	return x;
}

struct Hash {
	const ll base = 31;
	ll mod, *h, *pot;
	string s;

	Hash () {}

	void build (string s, ll mod) { // O(n)
		this->mod = mod;
		this->s = s;
		h = new ll [s.size() + 2];
		pot = new ll [s.size() + 2];

		h[0] = s[0] - 'a';
		for (int i = 1; i < (int)s.size(); i++) 
			h[i] = (h[i-1]*base + s[i] - 'a')%mod;

		pot[0] = 1LL;
		for (int i = 1; i < (int)s.size(); i++)
			pot[i] = (pot[i-1] * base)%mod;
	}

	ll query (int l, int r) { // O(1)
		ll R = h[r], L = 0; 

		if (l) 
			L = (h[l-1] * pot[r - l + 1])%mod;

		return md (R - L, mod);
	}

} h[2];

// returns if s[i, i + ilen - 1] is lexicographically smaller than s[j, j + jlen - 1]
// not tested if ilen != jlen
bool comp (string &s, int i, int ilen, int j, int jlen) {
	int bot = 0, top = min (ilen, jlen) - 1;
	int id = -1;

	while (bot <= top) {
		int mid = (bot + top)>>1;

		ii pi = ii(h[0].query(i, i + mid), h[1].query(i, i + mid));
		ii pj = ii(h[0].query(j, j + mid), h[1].query(j, j + mid));
		if (pi == pj) {
			bot = mid + 1;
			id = mid;
		} else {
			top = mid - 1;
		}
	}

	if (id == min (ilen, jlen) - 1) {
		if (ilen != jlen)
			return ilen < jlen;
		return i < j;
	}

	return s[i + id + 1] < s[j + id + 1];
}

const ll mod[2] = {1000000007, 1000000009};
