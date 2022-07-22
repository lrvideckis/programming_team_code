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
		assert(l <= r);
		for (l = range_idx(l), r = range_idx(r); l < r; l >>= 1, r >>= 1) {
			if (l & 1) f(l++);
			if (r & 1) f(--r);
		}
	}
	template <typename F> void for_parents_down(int l, int r, F f) const {
		assert(l <= r);
		if (l == r) return;
		l = range_idx(l), r = range_idx(r);
		for (int i = __lg(l); ((l >> i) << i) != l; i--) f(l >> i);
		for (int i = __lg(r); ((r >> i) << i) != r; i--) f(r >> i);
	}
	template <typename F> void for_parents_up(int l, int r, F f) const {
		assert(l <= r);
		if (l == r) return;
		l = range_idx(l), r = range_idx(r);
		for (int v = l >> (__builtin_ctz(l) + 1); v; v >>= 1) f(v);
		for (int v = r >> (__builtin_ctz(r) + 1); v; v >>= 1) f(v);
	}
};
