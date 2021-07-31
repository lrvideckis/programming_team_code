struct fenwickTree {
	vector<ll> bit;
	fenwickTree(int n) : bit(n,0) {}
	void update(int idx, ll d) {
		for(; idx < (int)bit.size(); idx = idx | (idx+1))
			bit[idx] += d;
	}
	ll sum(int r) {
		ll ret = 0;
		for(; r >= 0; r = (r&(r+1))-1)
			ret += bit[r];
		return ret;
	}
	ll sum(int l, int r) {
		return sum(r) - sum(l-1);
	}
};
