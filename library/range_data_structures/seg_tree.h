#pragma once
//source: https://codeforces.com/blog/entry/18051, https://github.com/ecnerwala/cp-book/blob/master/src/seg_tree.hpp, https://github.com/yosupo06/Algorithm/blob/master/src/datastructure/segtree.hpp
struct seg_tree {
	using dt = long long;
	using ch = long long;
	static dt combine(const dt& l, const dt& r) {
		return min(l, r);
	}
	static const dt INF = 1e18;
	struct node {
		dt val;
		ch lazy;
		int l, r;//[l, r)
	};
	const int N, S/*smallest power of 2 >= N*/;
	vector<node> tree;
	//doesn't work with empty array
	seg_tree(const vector<dt>& arr) : N(ssize(arr)), S(1 << __lg(2 * N - 1)), tree(2 * N) {
		for (int i = 0; i < N; i++)
			tree[i + N] = {arr[i], 0, i, i + 1};
		rotate(tree.rbegin(), tree.rbegin() + S - N, tree.rbegin() + N);
		for (int i = N - 1; i >= 1; i--) {
			tree[i] = {
				combine(tree[2 * i].val, tree[2 * i + 1].val),
				0,
				tree[2 * i].l,
				tree[2 * i + 1].r
			};
		}
	}
	void apply(int v, ch change) {
		tree[v].val += change;
		tree[v].lazy += change;
	}
	void push(int v) {
		if (tree[v].lazy) {
			apply(2 * v, tree[v].lazy);
			apply(2 * v + 1, tree[v].lazy);
			tree[v].lazy = 0;
		}
	}
	void build(int v) {
		tree[v].val = combine(tree[2 * v].val, tree[2 * v + 1].val);
	}
	int to_leaf(int i) const {
		i += S;
		return i < 2 * N ? i : 2 * (i - N);
	}
	//update range [l, r)
	void update(int l, int r, ch change) {
		l = to_leaf(l), r = to_leaf(r);
		int lca_l_r = __lg((l - 1) ^ r);
		for (int lg = __lg(l); lg > __builtin_ctz(l); lg--) push(l >> lg);
		for (int lg = lca_l_r; lg > __builtin_ctz(r); lg--) push(r >> lg);
		for (int x = l, y = r; x < y; x >>= 1, y >>= 1) {
			if (x & 1) apply(x++, change);
			if (y & 1) apply(--y, change);
		}
		for (int lg = __builtin_ctz(r) + 1; lg <= lca_l_r; lg++) build(r >> lg);
		for (int lg = __builtin_ctz(l) + 1; lg <= __lg(l); lg++) build(l >> lg);
	}
	//query range [l, r)
	dt query(int l, int r) {
		l = to_leaf(l), r = to_leaf(r);
		int lca_l_r = __lg((l - 1) ^ r);
		for (int lg = __lg(l); lg > __builtin_ctz(l); lg--) push(l >> lg);
		for (int lg = lca_l_r; lg > __builtin_ctz(r); lg--) push(r >> lg);
		dt resl = INF, resr = INF;
		for (; l < r; l >>= 1, r >>= 1) {
			if (l & 1) resl = combine(resl, tree[l++].val);
			if (r & 1) resr = combine(tree[--r].val, resr);
		}
		return combine(resl, resr);
	}
};
