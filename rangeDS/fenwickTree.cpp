struct fenwickTree {
	vector<ll> bit;
	int n;
	fenwickTree() {
		n = (int)1e5+3;
		bit.assign(n,0);
	}
	ll sum(int r) {
		ll ret = 0;
		for(; r >= 0; r = (r&(r+1))-1)
			ret += bit[r];
		return ret;
	}
	void add(int idx, ll d) {
		for(; idx < n; idx = idx | (idx+1))
			bit[idx] += d;
	}
	ll sum(int l, int r) {
		return sum(r) - sum(l-1);
	}
}ft;
