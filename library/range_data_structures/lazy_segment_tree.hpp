/** @file */
#pragma once
/**
 * @see https://codeforces.com/blog/entry/18051
 *     https://github.com/ecnerwala/cp-book/blob/master/src/seg_tree.hpp
 *     https://github.com/yosupo06/Algorithm/blob/master/src/datastructure/segtree.hpp
 *
 * Internal nodes are [1, n), leaf nodes are [n, 2 * n).
 *
 * Rotating leaves makes it a single complete binary tree (instead of a set of
 * perfect binary trees). So now, even for non-power of 2 size:
 * - recursive seg tree works
 * - recursive tree walks AKA binary search works
 * - root is at tree[1]
 */
struct seg_tree {
	using dt = long long;
	using ch = long long;
	static dt combine(const dt& le, const dt& ri) {
		return min(le, ri);
	}
	static const dt UNIT = 1e18;
	struct node {
		dt val;
		ch lazy;
		int le, ri;
	};
	const int N, S /**< smallest power of 2 >= N */;
	vector<node> tree;
	seg_tree(const vector<dt>& arr) : N(ssize(arr)), S(N ? 1 << __lg(2 * N - 1) : 0), tree(2 * N) {
		for (int i = 0; i < N; i++)
			tree[i + N] = {arr[i], 0, i, i + 1};
		rotate(tree.rbegin(), tree.rbegin() + S - N, tree.rbegin() + N);
		for (int i = N - 1; i >= 1; i--) {
			tree[i] = {
				combine(tree[2 * i].val, tree[2 * i + 1].val),
				0,
				tree[2 * i].le,
				tree[2 * i + 1].ri
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
	/**
	 * @param le,ri defines range [le, ri)
	 */
	void update(int le, int ri, ch change) {
		assert(0 <= le && le <= ri && ri <= N);
		le = to_leaf(le), ri = to_leaf(ri);
		int lca_l_r = __lg((le - 1) ^ ri);
		for (int lg = __lg(le); lg > __builtin_ctz(le); lg--) push(le >> lg);
		for (int lg = lca_l_r; lg > __builtin_ctz(ri); lg--) push(ri >> lg);
		for (int x = le, y = ri; x < y; x >>= 1, y >>= 1) {
			if (x & 1) apply(x++, change);
			if (y & 1) apply(--y, change);
		}
		for (int lg = __builtin_ctz(ri) + 1; lg <= lca_l_r; lg++) build(ri >> lg);
		for (int lg = __builtin_ctz(le) + 1; lg <= __lg(le); lg++) build(le >> lg);
	}
	void update(int v /**< = 1 */, int le, int ri, ch change) {
		if (ri <= tree[v].le || tree[v].ri <= le) return;
		if (le <= tree[v].le && tree[v].ri <= ri) return apply(v, change);
		push(v);
		update(2 * v, le, ri, change);
		update(2 * v + 1, le, ri, change);
		build(v);
	}
	/**
	 * @param le,ri defines range [le, ri)
	 */
	dt query(int le, int ri) {
		assert(0 <= le && le <= ri && ri <= N);
		le = to_leaf(le), ri = to_leaf(ri);
		int lca_l_r = __lg((le - 1) ^ ri);
		for (int lg = __lg(le); lg > __builtin_ctz(le); lg--) push(le >> lg);
		for (int lg = lca_l_r; lg > __builtin_ctz(ri); lg--) push(ri >> lg);
		dt resl = UNIT, resr = UNIT;
		for (; le < ri; le >>= 1, ri >>= 1) {
			if (le & 1) resl = combine(resl, tree[le++].val);
			if (ri & 1) resr = combine(tree[--ri].val, resr);
		}
		return combine(resl, resr);
	}
	dt query(int v /**< = 1 */, int le, int ri) {
		if (ri <= tree[v].le || tree[v].ri <= le) return UNIT;
		if (le <= tree[v].le && tree[v].ri <= ri) return tree[v].val;
		push(v);
		return combine(query(2 * v, le, ri), query(2 * v + 1, le, ri));
	}
};
