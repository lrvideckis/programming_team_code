#pragma once

struct fenwickTree {
	vector<ll> bit;
	fenwickTree(int n) : bit(n,0) {}
	fenwickTree(const vector<ll> & a) : bit(a.size()) {
		if (a.empty()) return;
		bit[0] = a[0];
		for (int i = 1; i < (int)a.size(); i++)
			bit[i] = bit[i-1] + a[i];
		for (int i = (int)a.size() - 1; i > 0; i--) {
			int lower_i = (i & (i+1)) - 1;
			if (lower_i >= 0)
				bit[i] -= bit[lower_i];
		}
	}
	void update(int idx, ll d) {
		for(; idx < (int)bit.size(); idx = idx | (idx+1))
			bit[idx] += d;
	}
	ll sum(int r) const {
		ll ret = 0;
		for(; r >= 0; r = (r&(r+1))-1)
			ret += bit[r];
		return ret;
	}
	ll sum(int l, int r) const {
		return sum(r) - sum(l-1);
	}
};

struct rangeUpdatesAndPointQueries {
	fenwickTree ft;
	rangeUpdatesAndPointQueries(int n) : ft(n) {}
	rangeUpdatesAndPointQueries(vector<ll> arr) : ft(arr.size()) {
		for(int i = (int)arr.size()-1; i >= 1; i--) {
			arr[i] -= arr[i-1];
		}
		ft = fenwickTree(arr);
	}
	void updateRange(int l, int r, ll diff) {
		ft.update(l, diff);
		if(r+1 < (int)ft.bit.size())
			ft.update(r+1, -diff);
	}
	ll queryIdx(int idx) const {
		return ft.sum(idx);
	}
};
