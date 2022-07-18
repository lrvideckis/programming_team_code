#pragma once
//For point updates: either switch to policy based BST, or use sqrt decomposition
#include "../range_hook.h"
struct merge_sort_tree {
	range_hook rh;
	vector<vector<int>> tree;
	//RTE's when `arr` is empty
	merge_sort_tree(const vector<int>& arr) : rh(range_hook(arr.size())), tree(2 * rh.n) {
		for (int i = 0; i < rh.n; i++)
			tree[rh.leaf_idx(i)] = {arr[i]};
		for (int i = rh.n - 1; i >= 1; i--) {
			const auto& l = tree[2 * i];
			const auto& r = tree[2 * i + 1];
			merge(l.begin(), l.end(), r.begin(), r.end(), back_inserter(tree[i]));
		}
	}
	//How many values in range [l, r) are < x?
	//O(log^2(n))
	int query(int l, int r, int x) {
		int res = 0;
		rh.for_each(l, r, [&](int v) -> void {
			const vector<int>& val = tree[v];
			res += lower_bound(val.begin(), val.end(), x) - val.begin();
		});
		return res;
	}
};
