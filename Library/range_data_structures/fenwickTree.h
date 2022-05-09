#pragma once

//status: tested on random inputs; also tested on
//https://judge.yosupo.jp/problem/point_add_range_sum, lower_bound tested on
//https://judge.yosupo.jp/problem/predecessor_problem

template<class T>
struct fenwickTree {
	vector<T> bit;
	fenwickTree(int n) : bit(n, 0) {}
	fenwickTree(const vector<T>& a) : bit(a.size()) {
		if (a.empty()) return;
		bit[0] = a[0];
		for (int i = 1; i < (int) a.size(); i++)
			bit[i] = bit[i - 1] + a[i];
		for (int i = (int) a.size() - 1; i > 0; i--) {
			int lower_i = (i & (i + 1)) - 1;
			if (lower_i >= 0)
				bit[i] -= bit[lower_i];
		}
	}
	void update(int idx, const T& d) {
		for (; idx < (int) bit.size(); idx = idx | (idx + 1))
			bit[idx] += d;
	}
	T sum(int r) const {
		T ret = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1)
			ret += bit[r];
		return ret;
	}
	T sum(int l, int r) const {
		return sum(r) - sum(l - 1);
	}
	//min pos st sum of [0, pos] >= sum
	// Returns bit.size() if no sum is >= sum, or -1 if empty sum is.
	int lower_bound(T sum) {
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1<<(31 - __builtin_clz(bit.size()|1)); pw; pw >>= 1) {
			if (pos + pw <= (int)bit.size() && bit[pos + pw-1] < sum)
				pos += pw, sum -= bit[pos-1];
		}
		return pos;
	}
};

//status: tested on random inputs

template<class T>
struct rangeUpdatesAndPointQueries {
	fenwickTree<T> ft;
	rangeUpdatesAndPointQueries(int n) : ft(n) {}
	rangeUpdatesAndPointQueries(const vector<T>& arr) : ft(init(arr)) {}
	fenwickTree<T> init(vector<T> arr/*intentional pass by value*/) {
		for (int i = (int) arr.size() - 1; i >= 1; i--)
			arr[i] -= arr[i - 1];
		return fenwickTree<T> (arr);
	}
	//add `add` to inclusive range [l, r]
	void updateRange(int l, int r, const T& add) {
		ft.update(l, add);
		if (r + 1 < (int) ft.bit.size())
			ft.update(r + 1, -add);
	}
	//get value at index `idx`
	T queryIdx(int idx) const {
		return ft.sum(idx);
	}
};
