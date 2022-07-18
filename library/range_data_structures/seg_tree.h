#pragma once
//stress tests: tests/stress_tests/range_data_structures/seg_tree.cpp
//source: https://codeforces.com/blog/entry/18051, https://github.com/ecnerwala/cp-book/blob/master/src/seg_tree.hpp, https://github.com/yosupo06/Algorithm/blob/master/src/datastructure/segtree.hpp
//floor of log_2(a); index of highest 1-bit
int log_2(int a) {
	return a ? (8 * sizeof(a)) - 1 - __builtin_clz(a) : -1;
}
struct range_hook {
	const int n, lg;//lg is the smallest integer satisfying 2^lg >= n
	range_hook(int a_n) : n(a_n), lg(log_2(2 * n - 1)) {}
	int leaf_idx(int i) const {
		assert(0 <= i && i < n);
		i += 1 << lg;
		return i < 2 * n ? i : i - n;
	}
	int range_idx(int i) const {
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
	//calls function `f` on ancestors of nodes making up range [l, r), bottom up
	template <typename F> void for_pars_up(int l, int r, F f) const {
		assert(0 <= l && l <= r && r <= n);
		for (int i = 1, a = range_idx(l), b = range_idx(r); i <= lg; i++) {
			if (((a >> i) << i) != a) f(a >> i);
			if (((b >> i) << i) != b) f((b - 1) >> i);
		}
	}
	//calls function `f` on ancestors of nodes making up range [l, r), top down
	template <typename F> void for_pars_down(int l, int r, F f) const {
		assert(0 <= l && l <= r && r <= n);
		for (int i = lg, a = range_idx(l), b = range_idx(r); i >= 1; i--) {
			if (((a >> i) << i) != a) f(a >> i);
			if (((b >> i) << i) != b) f((b - 1) >> i);
		}
	}
};
const long long inf = 1e18;
struct seg_tree {
	using dt /*data type*/ = array<long long, 3>; //sum, max, min
	struct node {
		dt val;
		long long lazy;
		int l, r;//[l, r)
		int len() const {
			return r - l;
		}
	};
	range_hook rh;
	vector<node> tree;
	//RTE's when `arr` is empty
	seg_tree(const vector<long long>& arr) : rh(range_hook(arr.size())), tree(2 * rh.n) {
		for (int i = 0; i < rh.n; i++) {
			tree[rh.leaf_idx(i)] = {
				{arr[i], arr[i], arr[i]},
				0,
				i,
				i + 1
			};
		}
		for (int i = rh.n - 1; i >= 1; i--) {
			tree[i] = {
				pull(tree[2 * i].val, tree[2 * i + 1].val),
				0,
				tree[2 * i].l,
				tree[2 * i + 1].r
			};
		}
	}
	//what happens when `add` is applied to every index in range [tree[v].l, tree[v].r)?
	void apply(int v, long long add) {
		tree[v].val[0] += tree[v].len() * add;
		tree[v].val[1] += add;
		tree[v].val[2] += add;
		tree[v].lazy += add;
	}
	void push(int v) {
		if (tree[v].lazy) {
			apply(2 * v, tree[v].lazy);
			apply(2 * v + 1, tree[v].lazy);
			tree[v].lazy = 0;
		}
	}
	static dt pull(const dt& l, const dt& r) {
		return {
			l[0] + r[0],
			max(l[1], r[1]),
			min(l[2], r[2])
		};
	}
	//update range [l,r) with `add`
	void update(int l, int r, long long add) {
		rh.for_pars_down(l, r, [&](int v) -> void {
			push(v);
		});
		rh.for_each(l, r, [&](int v) -> void {
			apply(v, add);
		});
		rh.for_pars_up(l, r, [&](int v) -> void {
			tree[v].val = pull(tree[2 * v].val, tree[2 * v + 1].val);
		});
	}
	void update(int v/* = 1*/, int l, int r, long long add) {
		if (r <= tree[v].l || tree[v].r <= l)
			return;
		if (l <= tree[v].l && tree[v].r <= r)
			return apply(v, add);
		push(v);
		update(2 * v, l, r, add);
		update(2 * v + 1, l, r, add);
		tree[v].val = pull(tree[2 * v].val, tree[2 * v + 1].val);
	}
	//query range [l,r)
	dt query(int l, int r) {
		rh.for_pars_down(l, r, [&](int v) -> void {
			push(v);
		});
		dt res = {0, -inf, inf};
		rh.for_each(l, r, [&](int v) -> void {
			res = pull(res, tree[v].val);
		});
		return res;
	}
	dt query(int v/* = 1*/, int l, int r) {
		if (r <= tree[v].l || tree[v].r <= l)
			return {0, -inf, inf};
		if (l <= tree[v].l && tree[v].r <= r)
			return tree[v].val;
		push(v);
		return pull(query(2 * v, l, r), query(2 * v + 1, l, r));
	}
};
