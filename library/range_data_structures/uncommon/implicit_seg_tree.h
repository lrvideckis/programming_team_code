#pragma once
//example initialization:
//	implicit_seg_tree<10'000'000> ist(l, r);
const long long inf = 1e18;
template <int N> struct implicit_seg_tree {
	using dt = array<long long, 3>; //sum, max, min
	struct node {
		dt val;
		long long lazy;
		int lch, rch; // children, indexes into `tree`, -1 for null
		node() {}
		node(const dt& a_val) : val(a_val), lazy(0), lch(-1), rch(-1) {}
	} tree[N];
	int ptr, root_l, root_r;//[root_l, root_r) defines range of root node; handles negatives
	implicit_seg_tree(int l, int r) : ptr(0), root_l(l), root_r(r) {
		tree[ptr++] = node(dt{0, 0, 0});
	}
	//what happens when `add` is applied to every index in range [tl, tr)?
	void apply(int v, int tl, int tr, long long add) {
		tree[v].val[0] += (tr - tl) * add;
		tree[v].val[1] += add;
		tree[v].val[2] += add;
		tree[v].lazy += add;
	}
	void push(int v, int tl, int tr) {
		if (tr - tl > 1 && tree[v].lch == -1) {
			assert(ptr + 1 < N);
			tree[v].lch = ptr;
			tree[ptr++] = node(dt{0, 0, 0});
			tree[v].rch = ptr;
			tree[ptr++] = node(dt{0, 0, 0});
		}
		if (tree[v].lazy) {
			int tm = tl + (tr - tl) / 2;
			apply(tree[v].lch, tl, tm, tree[v].lazy);
			apply(tree[v].rch, tm, tr, tree[v].lazy);
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
		update(0, root_l, root_r, l, r, add);
	}
	void update(int v, int tl, int tr, int l, int r, long long add) {
		if (r <= tl || tr <= l)
			return;
		if (l <= tl && tr <= r)
			return apply(v, tl, tr, add);
		push(v, tl, tr);
		int tm = tl + (tr - tl) / 2;
		update(tree[v].lch, tl, tm, l, r, add);
		update(tree[v].rch, tm, tr, l, r, add);
		tree[v].val = pull(tree[tree[v].lch].val,
		                   tree[tree[v].rch].val);
	}
	//query range [l,r)
	dt query(int l, int r) {
		return query(0, root_l, root_r, l, r);
	}
	dt query(int v, int tl, int tr, int l, int r) {
		if (r <= tl || tr <= l)
			return {0, -inf, inf};
		if (l <= tl && tr <= r)
			return tree[v].val;
		push(v, tl, tr);
		int tm = tl + (tr - tl) / 2;
		return pull(query(tree[v].lch, tl, tm, l, r),
		            query(tree[v].rch, tm, tr, l, r));
	}
};
