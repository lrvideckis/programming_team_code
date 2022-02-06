#pragma once

//status: tested on random inputs; also tested on https://judge.yosupo.jp/problem/point_add_range_sum

template<class T>
struct fenwickTree {
	vector<T> bit;
	fenwickTree(int n) : bit(n,0) {}
	fenwickTree(const vector<T>& a) : bit(a.size()) {
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
	void update(int idx, const T& d) {
		for(; idx < (int)bit.size(); idx = idx | (idx+1))
			bit[idx] += d;
	}
	T sum(int r) const {
		T ret = 0;
		for(; r >= 0; r = (r&(r+1))-1)
			ret += bit[r];
		return ret;
	}
	T sum(int l, int r) const {
		return sum(r) - sum(l-1);
	}
};

//status: tested on random inputs

template<class T>
struct rangeUpdatesAndPointQueries {
	fenwickTree<T> ft;
	rangeUpdatesAndPointQueries(int n) : ft(n) {}
	rangeUpdatesAndPointQueries(vector<T> arr) : ft(0) {
		for(int i = (int)arr.size()-1; i >= 1; i--) {
			arr[i] -= arr[i-1];
		}
		ft = fenwickTree<T>(arr);
	}
	void updateRange(int l, int r, const T& diff) {
		ft.update(l, diff);
		if(r+1 < (int)ft.bit.size())
			ft.update(r+1, -diff);
	}
	T queryIdx(int idx) const {
		return ft.sum(idx);
	}
};
