#pragma once
//source: https://codeforces.com/blog/entry/18051, https://github.com/ecnerwala/cp-book/blob/master/src/seg_tree.hpp, https://github.com/yosupo06/Algorithm/blob/master/src/datastructure/segtree.hpp
#include "../misc/helpers.h"
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
	//calls function `f` on all nodes making up range [l, r)
	template <typename F> void for_each(int l, int r, F f) const {
		assert(0 <= l && l <= r && r <= n);
		for (l = range_idx(l), r = range_idx(r); l < r; l >>= 1, r >>= 1) {
			if (l & 1) f(l++);
			if (r & 1) f(--r);
		}
	}
	//calls function `f` on ancestors of nodes making up range [l, r), if `up`: bottom up, else top down
	template <typename F> void for_pars(int l, int r, bool up, F f) const {
		assert(0 <= l && l <= r && r <= n);
		l = range_idx(l), r = range_idx(r);
		for (int i = (up ? 1 : lg); i != (up ? lg + 1 : 0); i += 2 * up - 1) {
			if (((l >> i) << i) != l) f(l >> i);
			if (((r >> i) << i) != r) f((r - 1) >> i);
		}
	}
};
