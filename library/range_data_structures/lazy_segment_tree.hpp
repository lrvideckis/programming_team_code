/** @file */
#pragma once
int split(int tl, int tr) {
	int pow_2 = 1 << __lg(tr - tl);
	return min(tl + pow_2, tr - pow_2 / 2);
}
long long op(long long vl, long long vr) {
	return vl + vr;
}
/**
 * @see https://codeforces.com/blog/entry/112755
 *
 * update: range add, query: range sum
 *
 * internal nodes are [1, n)
 * leaf nodes are [n, 2 * n)
 * root is at tree[1]
 */
struct seg_tree {
	const int N;
	vector<long long> tree, lazy;
	seg_tree(int n) : N(n), tree(2 * N), lazy(N) {}
	seg_tree(const vector<long long>& arr) : N(ssize(arr)), tree(2 * N), lazy(N) {
		rotate_copy(arr.begin(), arr.begin() + (N ? 2 * N - (2 << __lg(N)) : 0), arr.end(), tree.begin() + N);
		for (int i = N - 1; i >= 1; i--) pull(i);
	}
	void pull(int v) {tree[v] = op(tree[2 * v], tree[2 * v + 1]);}
	void apply(int v, int tl, int tr, long long change) {
		tree[v] += (tr - tl) * change;
		if (v < N) lazy[v] += change;
	}
	void push(int v, int tl, int tm, int tr) {
		if (lazy[v]) {
			apply(2 * v, tl, tm, lazy[v]);
			apply(2 * v + 1, tm, tr, lazy[v]);
			lazy[v] = 0;
		}
	}
	/**
	 * @param le,ri defines range [le, ri)
	 */
	void update(int le, int ri, long long change) {update(1, 0, N, le, ri, change);}
	void update(int v, int tl, int tr, int le, int ri, long long change) {
		if (ri <= tl || tr <= le) return;
		if (le <= tl && tr <= ri) return apply(v, tl, tr, change);
		int tm = split(tl, tr);
		push(v, tl, tm, tr);
		update(2 * v, tl, tm, le, ri, change);
		update(2 * v + 1, tm, tr, le, ri, change);
		pull(v);
	}
	/**
	 * @param le,ri defines range [le, ri)
	 */
	long long query(int le, int ri) {return query(1, 0, N, le, ri);}
	long long query(int v, int tl, int tr, int le, int ri) {
		if (ri <= tl || tr <= le) return 0;
		if (le <= tl && tr <= ri) return tree[v];
		int tm = split(tl, tr);
		push(v, tl, tm, tr);
		return op(query(2 * v, tl, tm, le, ri),
				  query(2 * v + 1, tm, tr, le, ri));
	}
};
