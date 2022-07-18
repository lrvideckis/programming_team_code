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
	};
	vector<node> tree;
	//RTE's when `arr` is empty
	seg_tree(const vector<long long>& arr) : tree(4 * arr.size()) {
		build(arr, 1, 0, (int)arr.size() - 1);
	}
	void build(const vector<long long>& arr, int v, int tl, int tr) {
		if (tl == tr) {
			tree[v] = {
				{arr[tl], arr[tl], arr[tl]},
				0,
				tl,
				tr
			};
		} else {
			int tm = tl + (tr - tl) / 2;
			build(arr, 2 * v, tl, tm);
			build(arr, 2 * v + 1, tm + 1, tr);
			tree[v] = {
				pull(tree[2 * v].val, tree[2 * v + 1].val),
				0,
				tl,
				tr
			};
		}
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
	//update range [l,r] with `add`
	void update(int l, int r, long long add) {
		update(1, l, r, add);
	}
	void update(int v, int l, int r, long long add) {
		if (tree[v].r < l || r < tree[v].l)
			return;
		if (l <= tree[v].l && tree[v].r <= r)
			return apply(v, add);
		push(v);
		update(2 * v, l, r, add);
		update(2 * v + 1, l, r, add);
		tree[v].val = pull(tree[2 * v].val,
		                   tree[2 * v + 1].val);
	}
	//query range [l,r]
	dt query(int l, int r) {
		return query(1, l, r);
	}
	dt query(int v, int l, int r) {
		if (tree[v].r < l || r < tree[v].l)
			return {0, -inf, inf};
		if (l <= tree[v].l && tree[v].r <= r)
			return tree[v].val;
		push(v);
		return pull(query(2 * v, l, r),
		            query(2 * v + 1, l, r));
	}
};
