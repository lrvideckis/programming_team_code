/** @file */
#pragma once
#include "../lazy_segment_tree.hpp"
/**
 * @see https://codeforces.com/blog/entry/18051
 *     https://github.com/ecnerwala/cp-book/blob/master/src/seg_tree.hpp
 *     https://github.com/yosupo06/Algorithm/blob/master/src/datastructure/segtree.hpp
 *
 * Iterative query and update functions access the exact same set of indexes as
 * their recursive counterparts.
 */
struct iter_seg_tree {
	const int S; /**< smallest power of 2 >= n */
	seg_tree st;
	iter_seg_tree(int n) : S(1 << __lg(2 * n - 1)), st(n) {}
	iter_seg_tree(const vector<long long>& arr) : S(1 << __lg(2 * ssize(arr) - 1)), st(arr) {}


	std::array<int, 2> get_node_bounds(int a) const {
		assert(1 <= a && a < 2 * st.N);
		int l = __builtin_clz(a) - __builtin_clz(2 * st.N - 1);
		int x = a << l, y = (a + 1) << l;
		assert(S <= x && x < y && y <= 2 * S);
		return {(x >= 2 * st.N ? (x >> 1) + st.N : x) - S, (y >= 2 * st.N ? (y >> 1) + st.N : y) - S};
	}


	int to_leaf(int i) const {
		i += S;
		return i < 2 * st.N ? i : 2 * (i - st.N);
	}
	/**
	 * @param le,ri defines range [le, ri)
	 */
	void update_iter(int le, int ri, long long change) {
		assert(0 <= le && le <= ri && ri <= st.N);
		le = to_leaf(le), ri = to_leaf(ri);
		int lca_l_r = __lg((le - 1) ^ ri);
		for (int lg = __lg(le); lg > __builtin_ctz(le); lg--) {
			auto [tl, tr] = get_node_bounds(le >> lg);
			st.push(le >> lg, tl, split(tl, tr), tr);
		}
		for (int lg = lca_l_r; lg > __builtin_ctz(ri); lg--) {
			auto [tl, tr] = get_node_bounds(ri >> lg);
			st.push(ri >> lg, tl, split(tl, tr), tr);
		}
		for (int x = le, y = ri; x < y; x >>= 1, y >>= 1) {
			if (x & 1) {
				auto [tl, tr] = get_node_bounds(x);
				st.apply(x++, tl, tr, change);
			}
			if (y & 1) {
				auto [tl, tr] = get_node_bounds(--y);
				st.apply(y, tl, tr, change);
			}
		}
		for (int lg = __builtin_ctz(ri) + 1; lg <= lca_l_r; lg++) st.pull(ri >> lg);
		for (int lg = __builtin_ctz(le) + 1; lg <= __lg(le); lg++) st.pull(le >> lg);
	}
	/**
	 * @param le,ri defines range [le, ri)
	 */
	long long query_iter(int le, int ri) {
		assert(0 <= le && le <= ri && ri <= st.N);
		le = to_leaf(le), ri = to_leaf(ri);
		int lca_l_r = __lg((le - 1) ^ ri);
		for (int lg = __lg(le); lg > __builtin_ctz(le); lg--) {
			auto [tl, tr] = get_node_bounds(le >> lg);
			st.push(le >> lg, tl, split(tl, tr), tr);
		}
		for (int lg = lca_l_r; lg > __builtin_ctz(ri); lg--) {
			auto [tl, tr] = get_node_bounds(ri >> lg);
			st.push(ri >> lg, tl, split(tl, tr), tr);
		}
		long long resl = 0, resr = 0;
		for (; le < ri; le >>= 1, ri >>= 1) {
			if (le & 1) resl = op(resl, st.tree[le++]);
			if (ri & 1) resr = op(st.tree[--ri], resr);
		}
		return op(resl, resr);
	}
};
