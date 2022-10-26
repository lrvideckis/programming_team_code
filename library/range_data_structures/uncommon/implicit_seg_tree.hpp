#pragma once
//example initialization:
//	implicit_seg_tree<10'000'000> ist(le, ri);
template <int N> struct implicit_seg_tree {
	using dt = array<long long, 2>;//min, number of mins
	using ch = long long;
	static dt combine(const dt& le, const dt& ri) {
		if (le[0] == ri[0]) return {le[0], le[1] + ri[1]};
		return min(le, ri);
	}
	static constexpr dt UNIT{(long long)1e18, 0LL};
	struct node {
		dt val;
		ch lazy = 0;
		int lch = -1, rch = -1; // children, indexes into `tree`, -1 for null
	} tree[N];
	int ptr = 0, root_l, root_r;//[root_l, root_r) defines range of root node; handles negatives
	implicit_seg_tree(int le, int ri) : root_l(le), root_r(ri) {
		tree[ptr++].val = {0, ri - le};
	}
	void apply(int v, ch add) {
		tree[v].val[0] += add;
		tree[v].lazy += add;
	}
	void push(int v, int tl, int tr) {
		if (tr - tl > 1 && tree[v].lch == -1) {
			int tm = tl + (tr - tl) / 2;
			assert(ptr + 1 < N);
			tree[v].lch = ptr;
			tree[ptr++].val = {0, tm - tl};
			tree[v].rch = ptr;
			tree[ptr++].val = {0, tr - tm};
		}
		if (tree[v].lazy) {
			apply(tree[v].lch, tree[v].lazy);
			apply(tree[v].rch, tree[v].lazy);
			tree[v].lazy = 0;
		}
	}
	//update range [le,ri)
	void update(int le, int ri, ch add) {
		update(0, root_l, root_r, le, ri, add);
	}
	void update(int v, int tl, int tr, int le, int ri, ch add) {
		if (ri <= tl || tr <= le)
			return;
		if (le <= tl && tr <= ri)
			return apply(v, add);
		push(v, tl, tr);
		int tm = tl + (tr - tl) / 2;
		update(tree[v].lch, tl, tm, le, ri, add);
		update(tree[v].rch, tm, tr, le, ri, add);
		tree[v].val = combine(tree[tree[v].lch].val,
							  tree[tree[v].rch].val);
	}
	//query range [le,ri)
	dt query(int le, int ri) {
		return query(0, root_l, root_r, le, ri);
	}
	dt query(int v, int tl, int tr, int le, int ri) {
		if (ri <= tl || tr <= le)
			return UNIT;
		if (le <= tl && tr <= ri)
			return tree[v].val;
		push(v, tl, tr);
		int tm = tl + (tr - tl) / 2;
		return combine(query(tree[v].lch, tl, tm, le, ri),
					   query(tree[v].rch, tm, tr, le, ri));
	}
};
