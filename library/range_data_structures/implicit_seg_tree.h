#pragma once
//stress tests: tests/stress_tests/range_data_structures/implicit_seg_tree.cpp
//see TODO for lines of code which usually need to change (not a complete list)
const int sz = 1.5e7; //TODO
struct node {
	long long val;//could represent max, sum, etc
	long long lazy;
	int lch, rch; // children, indexes into `tree`, -1 for null
} tree[sz];
struct implicit_seg_tree {
	int ptr, root_l, root_r;//[root_l, root_r] defines range of root node; handles negatives
	implicit_seg_tree(int l, int r) : ptr(0), root_l(l), root_r(r) {
		tree[ptr++] = {0, 0, -1, -1}; //TODO
	}
	static long long combine(long long val_l, long long val_r) {
		return val_l + val_r; //TODO
	}
	void apply(int v, int tl, int tr, long long add) {
		tree[v].val += (tr - tl + 1) * add; //TODO
		if (tl != tr) {
			tree[tree[v].lch].lazy += add; //TODO
			tree[tree[v].rch].lazy += add;
		}
	}
	void push(int v, int tl, int tr) {
		if (tl != tr && tree[v].lch == -1) {
			assert(ptr + 1 < sz);
			tree[v].lch = ptr;
			tree[ptr++] = {0, 0, -1, -1}; //TODO
			tree[v].rch = ptr;
			tree[ptr++] = {0, 0, -1, -1};
		}
		if (tree[v].lazy) {
			apply(v, tl, tr, tree[v].lazy);
			tree[v].lazy = 0;
		}
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
		tree[v].val = combine(tree[tree[v].lch].val, tree[tree[v].rch].val);
	}
	//query range [l,r]
	//for more complicated query which doesn't allocate new nodes, see:
	//https://github.com/lrvideckis/Programming-Team-Code/blob/dc659297850440b65af2550a834cc42af84b37f6/Library/range_data_structures/implicitLazySegTree.h
	long long query(int l, int r) {
		return query(0, root_l, root_r, l, r);
	}
	long long query(int v, int tl, int tr, int l, int r) {
		if (tr < l || r < tl)
			return 0; //TODO
		push(v, tl, tr);
		if (l <= tl && tr <= r)
			return tree[v].val;
		int tm = tl + (tr - tl) / 2;
		return combine(query(tree[v].lch, tl, tm, l, r),
		               query(tree[v].rch, tm + 1, tr, l, r));
	}
};
