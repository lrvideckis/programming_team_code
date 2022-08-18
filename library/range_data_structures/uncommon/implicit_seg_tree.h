#pragma once
//example initialization:
//	implicit_seg_tree<10'000'000> ist(l, r);
template <int N> struct implicit_seg_tree {
	using dt = array<long long, 2>;//min, number of mins
	using ch = long long;
	static dt combine(const dt& l, const dt& r) {
		if (l[0] == r[0]) return {l[0], l[1] + r[1]};
		return min(l, r);
	}
	static constexpr dt UNIT{(long long)1e18, 0LL};
	struct node {
		dt val;
		ch lazy;
		int lch, rch; // children, indexes into `tree`, -1 for null
		node() {}
		node(const dt& a_val) : val(a_val), lazy(0), lch(-1), rch(-1) {}
	} tree[N];
	int ptr, root_l, root_r;//[root_l, root_r) defines range of root node; handles negatives
	implicit_seg_tree(int l, int r) : ptr(0), root_l(l), root_r(r) {
		tree[ptr++] = node(dt{0, r - l});
	}
	void apply(int v, ch add) {
		tree[v].val[0] += add;
		tree[v].lazy += add;
	}
	void push(int v, int tl, int tr) {
		if (tr - tl > 1 && tree[v].lch == -1) {
			int mid = tl + (tr - tl) / 2;
			assert(ptr + 1 < N);
			tree[v].lch = ptr;
			tree[ptr++] = node(dt{0, mid - tl});
			tree[v].rch = ptr;
			tree[ptr++] = node(dt{0, tr - mid});
		}
		if (tree[v].lazy) {
			int tm = tl + (tr - tl) / 2;
			apply(tree[v].lch, tree[v].lazy);
			apply(tree[v].rch, tree[v].lazy);
			tree[v].lazy = 0;
		}
	}
	//update range [l,r)
	void update(int l, int r, ch add) {
		update(0, root_l, root_r, l, r, add);
	}
	void update(int v, int tl, int tr, int l, int r, ch add) {
		if (r <= tl || tr <= l)
			return;
		if (l <= tl && tr <= r)
			return apply(v, add);
		push(v, tl, tr);
		int tm = tl + (tr - tl) / 2;
		update(tree[v].lch, tl, tm, l, r, add);
		update(tree[v].rch, tm, tr, l, r, add);
		tree[v].val = combine(tree[tree[v].lch].val,
		                      tree[tree[v].rch].val);
	}
	//query range [l,r)
	dt query(int l, int r) {
		return query(0, root_l, root_r, l, r);
	}
	dt query(int v, int tl, int tr, int l, int r) {
		if (r <= tl || tr <= l)
			return UNIT;
		if (l <= tl && tr <= r)
			return tree[v].val;
		push(v, tl, tr);
		int tm = tl + (tr - tl) / 2;
		return combine(query(tree[v].lch, tl, tm, l, r),
		               query(tree[v].rch, tm, tr, l, r));
	}
};
