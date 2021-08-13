struct fenwickTree {
	vector<ll> bit;
	fenwickTree(int n) : bit(n,0) {}
	fenwickTree(vector<int> a) : fenwickTree(a.size()) {
		for (int i = 0; i < (int)a.size(); i++)
			add(i, a[i]);
	}
	void add(int idx, ll d) {
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
