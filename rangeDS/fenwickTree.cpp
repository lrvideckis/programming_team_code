struct fenwickTree {
	vector<ll> bit;
	fenwickTree(int n) : bit(n) {}
	fenwickTree(vector<int> a) : bit(a.size()) {
		bit[0] = a[0];
		for (int i = 1; i < (int)a.size(); i++)
			bit[i] = bit[i-1] + a[i];

		for (int i = a.size() - 1; i > 0; i--) {
			int lower_i = (i & (i+1)) - 1;
			if (lower_i >= 0)
				bit[i] -= bit[lower_i];
		}
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
