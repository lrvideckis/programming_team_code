#pragma once
//source: https://codeforces.com/blog/entry/18051
#include "range_hook.h"
const long long inf = 1e18;

struct seg_tree {
	using dt /*data type*/ = long long;//min
	static dt combine(const dt& l, const dt& r) {
		return min(l, r);
	}
	struct node {
		dt val;
		long long lazy;
		int l, r;//[l, r)
		int len() const {
			return r - l;
		}
	};
	const int n;
	vector<node> tree;
	seg_tree(const vector<long long>& arr) : n(arr.size()), tree(2 * n) {
		for (int i = 0, j = 1 << __lg(2 * n - 1); i < n; i++, j = (j + 1) % n + n) {
			tree[j] = {
				arr[i],
				0,
				i,
				i + 1
			};
		}
		for (int i = n - 1; i >= 1; i--) {
			tree[i] = {
				combine(tree[2 * i].val, tree[2 * i + 1].val),
				0,
				tree[2 * i].l,
				tree[2 * i + 1].r
			};
		}
	}
	//what happens when `add` is applied to every index in range [tree[v].l, tree[v].r)?
	void apply(int v, long long add) {
		tree[v].val += add;
		tree[v].lazy += add;
	}
	void push(int v) {
		if (tree[v].lazy) {
			apply(2 * v, tree[v].lazy);
			apply(2 * v + 1, tree[v].lazy);
			tree[v].lazy = 0;
		}
	}
	int range_idx(int i) const {
		i += 1 << __lg(2 * n - 1);
		return i < 2 * n ? i : 2 * (i - n);
	}
	void pars_down(int i) {
		for (int j = __lg(i); ((i >> j) << j) != i; j--) push(i >> j);
	}
	void pars_up(int i) {
		for (int v = i >> (__builtin_ctz(i) + 1); v; v >>= 1)
			tree[v].val = combine(tree[2 * v].val, tree[2 * v + 1].val);
	}
	//update range [l, r) with `add`
	void update(int l, int r, long long add) {
		l = range_idx(l), r = range_idx(r);
		pars_down(l), pars_down(r);
		{
			int l2 = l, r2 = r;
			for (; l < r; l >>= 1, r >>= 1) {
				if (l & 1) apply(l++, add);
				if (r & 1) apply(--r, add);
			}
			l = l2, r = r2;
		}
		pars_up(l), pars_up(r);
	}
	void update(int v/* = 1*/, int l, int r, long long add) {
		if (r <= tree[v].l || tree[v].r <= l)
			return;
		if (l <= tree[v].l && tree[v].r <= r)
			return apply(v, add);
		push(v);
		update(2 * v, l, r, add);
		update(2 * v + 1, l, r, add);
		tree[v].val = combine(tree[2 * v].val, tree[2 * v + 1].val);
	}
	//query range [l, r)
	dt query(int l, int r) {
		l = range_idx(l), r = range_idx(r);
		pars_down(l), pars_down(r);
		dt resl = inf, resr = inf;
		for (; l < r; l >>= 1, r >>= 1) {
			if (l & 1) resl = combine(resl, tree[l++].val);
			if (r & 1) resr = combine(tree[--r].val, resr);
		}
		return combine(resl, resr);
	}
	dt query(int v/* = 1*/, int l, int r) {
		if (r <= tree[v].l || tree[v].r <= l)
			return inf;
		if (l <= tree[v].l && tree[v].r <= r)
			return tree[v].val;
		push(v);
		return combine(query(2 * v, l, r), query(2 * v + 1, l, r));
	}
};
