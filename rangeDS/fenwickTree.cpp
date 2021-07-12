struct fenwickTree {
	vector<ll> bit;
	fenwickTree(int n) : bit(n,0) {}
	void add(int idx, int d) {
		for(; idx < (int)bit.size(); idx = idx | (idx+1))
			bit[idx] += d;
	}
 int sum(int r) {
	 int ret = 0;
		for(; r >= 0; r = (r&(r+1))-1)
			ret += bit[r];
		return ret;
	}
 int sum(int l, int r) {
		return sum(r) - sum(l-1);
	}
};
