/** @file */
#pragma once
int split(int tl, int tr) {
	int pow_2 = 1 << __lg(tr-tl);
	return min(tl + pow_2, tr - pow_2/2);
}
long long combine(long long vl, long long vr) {
	return vl + vr;
}
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
	const int N, S /**< smallest power of 2 >= N */;
	vector<long long> tree, lazy;
	seg_tree(const vector<long long>& arr) : N(ssize(arr)), S(N ? 1 << __lg(2 * N - 1) : 0), tree(2 * N), lazy(N) {
		rotate_copy(arr.begin(), arr.begin() + (2 * N - S), arr.end(), tree.begin() + N);
		for (int i = N - 1; i >= 1; i--) build(i);
	}
	void build(int v) {tree[v] = combine(tree[2 * v], tree[2 * v + 1]);}
	void apply(int v, int tl, int tr, long long change) {
		tree[v] += (tr - tl) * change;
		if(v < N) lazy[v] += change;
	}
	void push(int v, int tl, int tr) {
		if (lazy[v]) {
			int tm = split(tl, tr);
			apply(2 * v, tl, tm, lazy[v]);
			apply(2 * v + 1, tm, tr, lazy[v]);
			lazy[v] = 0;
		}
	}
	/*
	int to_leaf(int i) const {
		i += S;
		return i < 2 * N ? i : 2 * (i - N);
	}
	*/
	/**
	 * @param le,ri defines range [le, ri)
	 */
	/*
	void update_iter(int le, int ri, long long change) {
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
	*/
	/**
	 * @param le,ri defines range [le, ri)
	 */
	void update(int le, int ri, long long change) {update(1, 0, N, le, ri, change);}
	void update(int v, int tl, int tr, int le, int ri, long long change) {
		if (ri <= tl || tr <= le) return;
		if (le <= tl && tr <= ri) return apply(v, tl, tr, change);
		push(v, tl, tr);
		int tm = split(tl, tr);
		update(2 * v, tl, tm, le, ri, change);
		update(2 * v + 1, tm, tr, le, ri, change);
		build(v);
	}
	/**
	 * @param le,ri defines range [le, ri)
	 */
	/*
	long long query_iter(int le, int ri) {
		assert(0 <= le && le <= ri && ri <= N);
		le = to_leaf(le), ri = to_leaf(ri);
		int lca_l_r = __lg((le - 1) ^ ri);
		for (int lg = __lg(le); lg > __builtin_ctz(le); lg--) push(le >> lg);
		for (int lg = lca_l_r; lg > __builtin_ctz(ri); lg--) push(ri >> lg);
		long long resl = 0, resr = 0;
		for (; le < ri; le >>= 1, ri >>= 1) {
			if (le & 1) resl = combine(resl, tree[le++].val);
			if (ri & 1) resr = combine(tree[--ri].val, resr);
		}
		return combine(resl, resr);
	}
	*/
	/**
	 * @param le,ri defines range [le, ri)
	 */
	long long query(int le, int ri) {assert(0 <= le && le <= ri && ri <= N);return query(1, 0, N, le, ri);}
	long long query(int v, int tl, int tr, int le, int ri) {
		if (ri <= tl || tr <= le) return 0;
		if (le <= tl && tr <= ri) return tree[v];
		push(v, tl, tr);
		int tm = split(tl, tr);
		return combine(
			query(2 * v, tl, tm, le, ri),
			query(2 * v + 1, tm, tr, le, ri)
		);
	}
};
