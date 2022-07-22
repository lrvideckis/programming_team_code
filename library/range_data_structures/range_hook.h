#pragma once
//source: https://github.com/ecnerwala/cp-book/blob/master/src/seg_tree.hpp
struct range_hook {
	const int n, lg;//lg is the smallest integer satisfying 2^lg >= n
	range_hook(int a_n) : n(a_n), lg(__lg(2 * n - 1)) {}
	int leaf_idx(int i) const {//index in array -> index of leaf in seg_tree
		assert(0 <= i && i < n);
		i += 1 << lg;
		return i < 2 * n ? i : i - n;
	}
	int range_idx(int i) const {//range query bound -> index of leaf in seg_tree
		assert(0 <= i && i <= n);
		i += 1 << lg;
		return i < 2 * n ? i : 2 * (i - n);
	}
	// Iterate over the range from outside-in.
	//   Calls f(idx)
	template <typename F> void for_each(int l, int r, F f) const {
		assert(l <= r);
		for (l = range_idx(l), r = range_idx(r); l < r; l >>= 1, r >>= 1) {
			if (l & 1) f(l++, true);
			if (r & 1) f(--r, false);
		}
	}
	template <typename F> void for_parents_down(int i, F f) const {
		i = range_idx(i);
		for (int j = __lg(i); ((i >> j) << j) != i; j--) f(i >> j);
	}
	template <typename F> void for_parents_up(int i, F f) const {
		i = range_idx(i);
		for (int v = i >> (__builtin_ctz(i) + 1); v; v >>= 1) f(v);
	}
};
