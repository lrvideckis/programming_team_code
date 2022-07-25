#pragma once
//source: https://codeforces.com/blog/entry/18051
const long long INF = 1e18;
struct seg_tree {
	using dt /*data type*/ = long long;//min
	using ch /*data type*/ = long long;//add
	static dt combine(const dt& l, const dt& r) {
		return min(l, r);
	}
	struct node {
		dt val;
		ch lazy;
		int l, r;//[l, r)
	};
	const int N;
	vector<node> tree;
	seg_tree(const vector<long long>& arr) : N(arr.size()), tree(2 * N) {
		for (int i = 0, j = 1 << __lg(2 * N - 1); i < N; i++, j = (j + 1) % N + N)
			tree[j] = {arr[i], 0, i, i + 1};
		for (int i = N - 1; i >= 1; i--) {
			tree[i] = {
				combine(tree[2 * i].val, tree[2 * i + 1].val),
				0,
				tree[2 * i].l,
				tree[2 * i + 1].r
			};
		}
	}
	//what happens when `change` is applied to every index in range [tree[v].l, tree[v].r)?
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
	int range_idx(int i) const {
		i += 1 << __lg(2 * N - 1);
		return i < 2 * N ? i : 2 * (i - N);
	}
	//update range [l, r) with `change`
	void update(int l, int r, ch change) {
		l = range_idx(l), r = range_idx(r);
		for (int lg = __lg(l); lg >= 1; lg--) {
			if (((l >> lg) << lg) != l) push(l >> lg);
			if (((r >> lg) << lg) != r) push(r >> lg);
		}
		for (int x = l, y = r; x < y; x >>= 1, y >>= 1) {
			if (x & 1) apply(x++, change);
			if (y & 1) apply(--y, change);
		}
		for (int lg = 1; lg <= __lg(l); lg++) {
			if (((l >> lg) << lg) != l) build(l >> lg);
			if (((r >> lg) << lg) != r) build(r >> lg);
		}
	}
	//query range [l, r)
	dt query(int l, int r) {
		l = range_idx(l), r = range_idx(r);
		for (int lg = __lg(l); lg >= 1; lg--) {
			if (((l >> lg) << lg) != l) push(l >> lg);
			if (((r >> lg) << lg) != r) push(r >> lg);
		}
		dt resl = INF, resr = INF;
		for (; l < r; l >>= 1, r >>= 1) {
			if (l & 1) resl = combine(resl, tree[l++].val);
			if (r & 1) resr = combine(tree[--r].val, resr);
		}
		return combine(resl, resr);
	}
};
