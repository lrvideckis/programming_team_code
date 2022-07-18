#pragma once
//library checker tests: https://judge.yosupo.jp/problem/vertex_add_subtree_sum, https://judge.yosupo.jp/problem/point_add_range_sum
#include "../bit.h"
template<class T> struct bit_inv {
	BIT<T> ft;
	bit_inv(int n) : ft(n) {}
	bit_inv(const vector<T>& arr) : ft(init(arr)) {}
	BIT<T> init(vector<T> arr/*intentional pass by value*/) const {
		for (int i = (int)arr.size() - 1; i >= 1; i--)
			arr[i] -= arr[i - 1];
		return BIT<T>(arr);
	}
	//add `add` to range [l, r)
	void update(int l, int r, const T& add) {
		ft.update(l, add);
		if (r < (int)ft.bit.size())
			ft.update(r, -add);
	}
	//get value at index `idx`
	T query(int idx) const {
		return ft.sum(idx);
	}
};
