#pragma once
//source: https://codeforces.com/blog/entry/18051
#include "range_hook.h"
const long long inf = 1e18;
struct simple_seg_tree {
	using dt /*data type*/ = long long;//sum
	struct node {
		dt val;
		int l, r;//[l, r)
		int len() const {
			return r - l;
		}
	};
	range_hook rh;
	vector<node> tree;
	simple_seg_tree(const vector<long long>& arr) : rh(range_hook(arr.size())), tree(2 * rh.n) {
		for (int i = 0; i < rh.n; i++) {
			tree[rh.leaf_idx(i)] = {
				arr[i],
				i,
				i + 1
			};
		}
		for (int i = rh.n - 1; i >= 1; i--) {
			tree[i] = {
				pull(tree[2 * i].val, tree[2 * i + 1].val),
				tree[2 * i].l,
				tree[2 * i + 1].r
			};
		}
	}
	static dt pull(const dt& l, const dt& r) {
		return l + r;
	}
	//update range [l,r) with `add`
	void update(int idx, long long add) {
		tree[rh.leaf_idx(idx)].val += add;
		rh.for_parents_up(idx, idx + 1, [&](int v) -> void {
			tree[v].val = pull(tree[2 * v].val, tree[2 * v + 1].val);
		});
	}
	//query range [l,r)
	dt query(int l, int r) {
		dt res = 0;
		//switch out with for_each_l_to_r if order matters
		rh.for_each(l, r, [&](int v) -> void {
			res = pull(res, tree[v].val);
		});
		return res;
	}
};
