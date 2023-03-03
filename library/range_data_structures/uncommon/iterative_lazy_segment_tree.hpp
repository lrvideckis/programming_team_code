/** @file */
#pragma once
#include "../lazy_segment_tree.hpp"
/**
 * @see https://codeforces.com/blog/entry/18051
 *     https://github.com/ecnerwala/cp-book/blob/master/src/seg_tree.hpp
 *     https://github.com/yosupo06/Algorithm/blob/master/src/datastructure/segtree.hpp
 */
struct iter_seg_tree {
	seg_tree st;
	iter_seg_tree(int n) : st(n) {}
	iter_seg_tree(const vector<long long>& arr) : st(arr) {}
	int to_leaf(int i) const {
		i += S;
		return i < 2 * N ? i : 2 * (i - N);
	}
	/**
	 * @param le,ri defines range [le, ri)
	 */
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
		for (int lg = __builtin_ctz(ri) + 1; lg <= lca_l_r; lg++) pull(ri >> lg);
		for (int lg = __builtin_ctz(le) + 1; lg <= __lg(le); lg++) pull(le >> lg);
	}
	/**
	 * @param le,ri defines range [le, ri)
	 */
	long long query_iter(int le, int ri) {
		assert(0 <= le && le <= ri && ri <= N);
		le = to_leaf(le), ri = to_leaf(ri);
		int lca_l_r = __lg((le - 1) ^ ri);
		for (int lg = __lg(le); lg > __builtin_ctz(le); lg--) push(le >> lg);
		for (int lg = lca_l_r; lg > __builtin_ctz(ri); lg--) push(ri >> lg);
		long long resl = UNIT, resr = UNIT;
		for (; le < ri; le >>= 1, ri >>= 1) {
			if (le & 1) resl = combine(resl, tree[le++].val);
			if (ri & 1) resr = combine(tree[--ri].val, resr);
		}
		return combine(resl, resr);
	}
};
