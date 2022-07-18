#pragma once
//stress tests: tests/stress_tests/range_data_structures/seg_tree.cpp
const long long inf = 1e18;
struct seg_tree {
	using dt /*data type*/ = array<long long, 3>; //sum, max, min
	struct node {
		dt val;
		long long lazy;
		int l, r;
		int len() const {
			return r - l + 1;
		}
		//returns 1 + (# of nodes in left child's subtree)
		//https://cp-algorithms.com/data_structures/segment_tree.html#memory-efficient-implementation
		int rch() const { //right child
			return (r - l + 2) & ~1;
		}
	};
	vector<node> tree;
	//RTE's when `arr` is empty
	seg_tree(const vector<long long>& arr) : tree(2 * (int)arr.size() - 1) {
		int timer = 0;
		build(arr, timer, 0, (int)arr.size() - 1);
	}
	dt build(const vector<long long>& arr, int& timer, int tl, int tr) {
		node& curr = tree[timer++];
		curr.lazy = 0, curr.l = tl, curr.r = tr;
		if (tl == tr)
			return curr.val = {arr[tl], arr[tl], arr[tl]};
		int tm = tl + (tr - tl) / 2;
		dt l = build(arr, timer, tl, tm);
		dt r = build(arr, timer, tm + 1, tr);
		return curr.val = pull(l, r);
	}
	//what happens when `add` is applied to every index in range [tree[v].l, tree[v].r]?
	void apply(int v, long long add) {
		tree[v].val[0] += tree[v].len() * add;
		tree[v].val[1] += add;
		tree[v].val[2] += add;
		tree[v].lazy += add;
	}
	void push(int v) {
		if (tree[v].lazy) {
			apply(v + 1, tree[v].lazy);
			apply(v + tree[v].rch(), tree[v].lazy);
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
		update(0, l, r, add);
	}
	void update(int v, int l, int r, long long add) {
		if (tree[v].r < l || r < tree[v].l)
			return;
		if (l <= tree[v].l && tree[v].r <= r)
			return apply(v, add);
		push(v);
		update(v + 1, l, r, add);
		update(v + tree[v].rch(), l, r, add);
		tree[v].val = pull(tree[v + 1].val,
		                   tree[v + tree[v].rch()].val);
	}
	//query range [l,r]
	dt query(int l, int r) {
		return query(0, l, r);
	}
	dt query(int v, int l, int r) {
		if (tree[v].r < l || r < tree[v].l)
			return {0, -inf, inf};
		if (l <= tree[v].l && tree[v].r <= r)
			return tree[v].val;
		push(v);
		return pull(query(v + 1, l, r),
		            query(v + tree[v].rch(), l, r));
	}
};
