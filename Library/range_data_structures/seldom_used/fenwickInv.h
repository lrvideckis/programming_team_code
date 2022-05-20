#pragma once

#include "../fenwickTree.h"

//status: tested on random inputs

template<class T>
struct fenwickInv {
	fenwickTree<T> ft;
	fenwickInv(int n) : ft(n) {}
	fenwickInv(const vector<T>& arr) : ft(init(arr)) {}
	fenwickTree<T> init(vector<T> arr/*intentional pass by value*/) {
		for (int i = (int) arr.size() - 1; i >= 1; i--)
			arr[i] -= arr[i - 1];
		return fenwickTree<T> (arr);
	}
	//add `add` to inclusive range [l, r]
	void update(int l, int r, const T& add) {
		ft.update(l, add);
		if (r + 1 < (int) ft.bit.size())
			ft.update(r + 1, -add);
	}
	//get value at index `idx`
	T query(int idx) const {
		return ft.sum(idx);
	}
};
