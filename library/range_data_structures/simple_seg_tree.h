#pragma once
//source: https://codeforces.com/blog/entry/18051
#include "range_hook.h"
struct simple_seg_tree {
	using dt /*data type*/ = long long;//sum
	range_hook rh;
	vector<dt> tree;
	simple_seg_tree(const vector<dt>& arr) : rh(range_hook(arr.size())), tree(2 * rh.n) {
		for (int i = 0; i < rh.n; i++)
			tree[rh.leaf_idx(i)] = arr[i];
		for (int i = rh.n - 1; i >= 1; i--)
			tree[i] = pull(tree[2 * i], tree[2 * i + 1]);
	}
	static dt pull(const dt& l, const dt& r) {
		return l + r;
	}
	//update index `idx` with `add`
	void update(int idx, dt add) {
		tree[rh.leaf_idx(idx)] += add;
		rh.for_parents_up(idx, idx + 1, [&](int v) -> void {
			tree[v] = pull(tree[2 * v], tree[2 * v + 1]);
		});
	}
	//query range [l, r)
	dt query(int l, int r) {
		dt res = 0;
		//switch out with for_each_l_to_r if order matters
		rh.for_each(l, r, [&](int v) -> void {
			res = pull(res, tree[v]);
		});
		return res;
	}
};
