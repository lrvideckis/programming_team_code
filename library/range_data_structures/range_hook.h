#pragma once
//source: https://codeforces.com/blog/entry/18051, https://github.com/ecnerwala/cp-book/blob/master/src/seg_tree.hpp, https://github.com/yosupo06/Algorithm/blob/master/src/datastructure/segtree.hpp
#include "../misc/log_2.h"
struct range_hook {
	const int n, lg;//lg is the smallest integer satisfying 2^lg >= n
	range_hook(int a_n) : n(a_n), lg(log_2(2 * n - 1)) {}
	int leaf_idx(int i) const {//index in array -> index of leaf in seg_tree
		assert(0 <= i && i < n);
		i += 1 << lg;
		return i < 2 * n ? i : i - n;
	}
	int arr_idx(int i) const {//index of leaf in seg_tree -> index in array
		assert(n <= i && i < 2 * n);
		return (i < (1 << lg) ? i + n : i) - (1 << lg);
	}
	int range_idx(int i) const {//range query bound -> index of leaf in seg_tree
		assert(0 <= i && i <= n);
		i += 1 << lg;
		return i < 2 * n ? i : 2 * (i - n);
	}
	// Iterate over the range from outside-in.
	//   Calls f(idx)
	template <typename F> void for_each(int l, int r, F f) const {
		for (l = range_idx(l), r = range_idx(r); l < r; l >>= 1, r >>= 1) {
			if (l & 1) f(l++);
			if (r & 1) f(--r);
		}
	}
	// Iterate over the range from left to right.
	//    Calls f(idx)
	template <typename F> void for_each_l_to_r(int l, int r, F f) const {
		int a = range_idx(l), b = range_idx(r);
		int anc_depth = log_2((a - 1) ^ b);
		int anc_msk = (1 << anc_depth) - 1;
		for (int v = (-a) & anc_msk; v; v &= v - 1) {
			int i = __builtin_ctz(v);
			f(((a - 1) >> i) + 1);
		}
		for (int v = b & anc_msk; v;) {
			int i = log_2(v);
			f((b >> i) - 1);
			v ^= (1 << i);
		}
	}
	template <typename F> void for_parents_down(int l, int r, F f) const {
		int x = range_idx(l), y = range_idx(r);
		if ((x ^ y) > x)
			x <<= 1, swap(x, y);
		int dx = __builtin_ctz(x);
		int dy = __builtin_ctz(y);
		int anc_depth = log_2((x - 1) ^ y);
		for (int i = log_2(x); i > dx; i--)
			f(x >> i);
		for (int i = anc_depth; i > dy; i--)
			f(y >> i);
	}
	template <typename F> void for_parents_up(int l, int r, F f) const {
		int x = range_idx(l), y = range_idx(r);
		if ((x ^ y) > x)
			x <<= 1, swap(x, y);
		int dx = __builtin_ctz(x);
		int dy = __builtin_ctz(y);
		int anc_depth = log_2((x - 1) ^ y);
		for (int i = dx + 1; i <= anc_depth; i++)
			f(x >> i);
		for (int v = y >> (dy + 1); v; v >>= 1)
			f(v);
	}
};
