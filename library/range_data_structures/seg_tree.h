#pragma once
//stress tests: tests/stress_tests/range_data_structures/seg_tree.cpp
//source: https://codeforces.com/blog/entry/18051, https://github.com/ecnerwala/cp-book/blob/master/src/seg_tree.hpp, https://github.com/yosupo06/Algorithm/blob/master/src/datastructure/segtree.hpp
#include "range_hook.h"
const long long inf = 1e18;
struct seg_tree {
	using dt /*data type*/ = array<long long, 3>; //sum, max, min
	struct node {
		dt val;
		long long lazy;
		int l, r;//[l, r)
		int len() const {
			return r - l;
		}
	};
	range_hook rh;
	vector<node> tree;
	//RTE's when `arr` is empty
	seg_tree(const vector<long long>& arr) : rh(range_hook(arr.size())), tree(2 * rh.n) {
		for (int i = 0; i < rh.n; i++) {
			tree[rh.leaf_idx(i)] = {
				{arr[i], arr[i], arr[i]},
				0,
				i,
				i + 1
			};
		}
		for (int i = rh.n - 1; i >= 1; i--) {
			tree[i] = {
				pull(tree[2 * i].val, tree[2 * i + 1].val),
				0,
				tree[2 * i].l,
				tree[2 * i + 1].r
			};
		}
	}
	//what happens when `add` is applied to every index in range [tree[v].l, tree[v].r)?
	void apply(int v, long long add) {
		tree[v].val[0] += tree[v].len() * add;
		tree[v].val[1] += add;
		tree[v].val[2] += add;
		tree[v].lazy += add;
	}
	void push(int v) {
		if (tree[v].lazy) {
			apply(2 * v, tree[v].lazy);
			apply(2 * v + 1, tree[v].lazy);
			tree[v].lazy = 0;
		}
	}
	static dt pull(const dt& l, const dt& r) {
		return {
			l[0] + r[0],
			max(l[1], r[1]),
			min(l[2], r[2])
		};
	}
	//update range [l,r) with `add`
	void update(int l, int r, long long add) {
		rh.for_pars(l, r, false, [&](int v) -> void {
			push(v);
		});
		rh.for_each(l, r, [&](int v) -> void {
			apply(v, add);
		});
		rh.for_pars(l, r, true, [&](int v) -> void {
			tree[v].val = pull(tree[2 * v].val, tree[2 * v + 1].val);
		});
	}
	void update(int v/* = 1*/, int l, int r, long long add) {
		if (r <= tree[v].l || tree[v].r <= l)
			return;
		if (l <= tree[v].l && tree[v].r <= r)
			return apply(v, add);
		push(v);
		update(2 * v, l, r, add);
		update(2 * v + 1, l, r, add);
		tree[v].val = pull(tree[2 * v].val, tree[2 * v + 1].val);
	}
	//query range [l,r)
	dt query(int l, int r) {
		rh.for_pars(l, r, false, [&](int v) -> void {
			push(v);
		});
		dt res = {0, -inf, inf};
		rh.for_each(l, r, [&](int v) -> void {
			res = pull(res, tree[v].val);
		});
		return res;
	}
	dt query(int v/* = 1*/, int l, int r) {
		if (r <= tree[v].l || tree[v].r <= l)
			return {0, -inf, inf};
		if (l <= tree[v].l && tree[v].r <= r)
			return tree[v].val;
		push(v);
		return pull(query(2 * v, l, r), query(2 * v + 1, l, r));
	}
};
