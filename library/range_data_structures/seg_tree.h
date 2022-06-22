#pragma once
//stress tests: tests/stress_tests/range_data_structures/seg_tree.cpp
const long long inf = 1e18;
struct seg_tree {
	struct node {
		long long sum, mx, mn;
		long long lazy;
		int l, r;
		int len() const {
			return r - l + 1;
		}
		//returns 1 + (# of nodes in left child's subtree)
		//https://cp-algorithms.com/data_structures/segment_tree.html#memory-efficient-implementation
		//Now, a seg tree over an array of length n requires only 2*n-1 nodes
		//which are n leaf nodes and n-1 internal nodes. n-1 internal nodes is
		//minimal as each internal node can only combine 2 childs into 1.
		int rch() const { //right child
			return ((r - l) & ~1) + 2;
		}
	};
	vector<node> tree;
	//There's no constructor `seg_tree(int size)` because how to initialize l,r in nodes without calling build?
	//the whole point of `seg_tree(int size)` was to be simpler by not calling build
	seg_tree(const vector<long long>& arr) : tree(2 * (int)arr.size() - 1) {
		build(arr, 0, 0, (int)arr.size() - 1);
	}
	void build(const vector<long long>& arr, int v, int tl, int tr) {
		if (tl == tr) {
			tree[v] = {
				arr[tl],
				arr[tl],
				arr[tl],
				0,
				tl,
				tr
			};
		} else {
			int tm = tl + (tr - tl) / 2;
			build(arr, v + 1, tl, tm);
			build(arr, v + 2 * (tm - tl + 1), tm + 1, tr);
			tree[v] = combine(tree[v + 1], tree[v + 2 * (tm - tl + 1)]);
		}
	}
	static node combine(const node& l, const node& r) {
		return {
			l.sum + r.sum,
			max(l.mx, r.mx),
			min(l.mn, r.mn),
			0,
			l.l,
			r.r
		};
	}
	//what happens when `add` is applied to every index in range [tree[v].l, tree[v].r]?
	void apply(int v, long long add) {
		tree[v].sum += tree[v].len() * add;
		tree[v].mx += add;
		tree[v].mn += add;
		if (tree[v].len() > 1) {
			tree[v + 1].lazy += add;
			tree[v + tree[v].rch()].lazy += add;
		}
	}
	void push(int v) {
		if (tree[v].lazy) {
			apply(v, tree[v].lazy);
			tree[v].lazy = 0;
		}
	}
	//update range [l,r] with `add`
	void update(int l, int r, long long add) {
		update(0, l, r, add);
	}
	void update(int v, int l, int r, long long add) {
		push(v);
		if (tree[v].r < l || r < tree[v].l)
			return;
		if (l <= tree[v].l && tree[v].r <= r)
			return apply(v, add);
		update(v + 1, l, r, add);
		update(v + tree[v].rch(), l, r, add);
		tree[v] = combine(tree[v + 1], tree[v + tree[v].rch()]);
	}
	//range [l,r]
	node query(int l, int r) {
		return query(0, l, r);
	}
	node query(int v, int l, int r) {
		if (tree[v].r < l || r < tree[v].l)
			return {0, -inf, inf, 0, 0, 0};
		push(v);
		if (l <= tree[v].l && tree[v].r <= r)
			return tree[v];
		return combine(query(v + 1, l, r),
		               query(v + tree[v].rch(), l, r));
	}
};
