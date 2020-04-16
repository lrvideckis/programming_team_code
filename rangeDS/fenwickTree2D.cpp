struct fenwickTree2D {
	vector<vector<ll>> bit;
	int n, m;
	//2D matrix, with n rows, and m columns
	fenwickTree2D(int _n, int _m) {
		n = _n;
		m = _m;
		bit.resize(n+1, vector<ll>(m+1,0));
	}
	//returns sum of rows [0..i], and [0..j] inclusive
	ll sum(int i, int j) {
		ll ret = 0;
		for(; i >= 0; i = (i&(i+1))-1)
			for(int jj = j; jj >= 0; jj = (jj&(jj+1))-1)
				ret += bit[i][jj];
		return ret;
	}
	//adds value to location i,j
	void add(int i, int j, ll d) {
		for(; i <= n; i = i | (i+1))
			for(int jj = j; jj <= m; jj = jj | (jj+1))
				bit[i][jj] += d;
	}
};
