#pragma once
//stress tests: tests/stress_tests/range_data_structures/implicit_seg_tree.cpp
using dt = array<long long, 3>; //sum, max, min
const long long inf = 1e18;
const int sz = 1.5e7;
struct node {
	dt val;
	long long lazy;
	int lch, rch; // children, indexes into `tree`, -1 for null
	node() {}
	node(const dt& a_val) : val(a_val) {
		lazy = 0, lch = rch = -1;
	}
} tree[sz];
struct implicit_seg_tree {
	int ptr, root_l, root_r;//[root_l, root_r] defines range of root node; handles negatives
	//RTE's when `arr` is empty
	implicit_seg_tree(int l, int r) : ptr(0), root_l(l), root_r(r) {
		tree[ptr++] = node(dt{0, 0, 0});
	}
	//what happens when `add` is applied to every index in range [tl, tr]?
	void apply(int v, int tl, int tr, long long add) {
		tree[v].val[0] += (tr - tl + 1) * add;
		tree[v].val[1] += add;
		tree[v].val[2] += add;
		if (tl != tr) {
			tree[tree[v].lch].lazy += add;
			tree[tree[v].rch].lazy += add;
		}
	}
	void push(int v, int tl, int tr) {
		if (tl != tr && tree[v].lch == -1) {
			assert(ptr + 1 < sz);
			tree[v].lch = ptr;
			tree[ptr++] = node(dt{0, 0, 0});
			tree[v].rch = ptr;
			tree[ptr++] = node(dt{0, 0, 0});
		}
		if (tree[v].lazy) {
			apply(v, tl, tr, tree[v].lazy);
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
	//update range [l,r] with `add`
	void update(int l, int r, long long add) {
		update(0, root_l, root_r, l, r, add);
	}
	void update(int v, int tl, int tr, int l, int r, long long add) {
		push(v, tl, tr);
		if (tr < l || r < tl)
			return;
		if (l <= tl && tr <= r)
			return apply(v, tl, tr, add);
		int tm = tl + (tr - tl) / 2;
		update(tree[v].lch, tl, tm, l, r, add);
		update(tree[v].rch, tm + 1, tr, l, r, add);
		tree[v].val = pull(tree[tree[v].lch].val, tree[tree[v].rch].val);
	}
	//query range [l,r]
	dt query(int l, int r) {
		return query(0, root_l, root_r, l, r);
	}
	dt query(int v, int tl, int tr, int l, int r) {
		if (tr < l || r < tl)
			return {0, -inf, inf};
		push(v, tl, tr);
		if (l <= tl && tr <= r)
			return tree[v].val;
		int tm = tl + (tr - tl) / 2;
		return pull(query(tree[v].lch, tl, tm, l, r),
		            query(tree[v].rch, tm + 1, tr, l, r));
	}
};
