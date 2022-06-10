#pragma once
//library checker tests: https://judge.yosupo.jp/problem/static_range_frequency, https://judge.yosupo.jp/problem/range_kth_smallest
//For point updates: either switch to policy based BST, or use sqrt decomposition
struct merge_sort_tree {
	struct node {
		vector<int> vals;
		int l, r;
		//returns 1 + (# of nodes in left child's subtree)
		//https://cp-algorithms.com/data_structures/segment_tree.html#memory-efficient-implementation
		int r_ch() const {
			return ((r - l) & ~1) + 2;
		}
	};
	vector<node> tree;
	//RTE's when `arr` is empty
	merge_sort_tree(const vector<int>& arr) : tree(2 * (int)arr.size() - 1) {
		build(arr, 0, 0, (int)arr.size() - 1);
	}
	void build(const vector<int>& arr, int v, int tl, int tr) {
		if (tl == tr) {
			tree[v] = {
				{arr[tl]},
				tl,
				tr
			};
		} else {
			int tm = tl + (tr - tl) / 2;
			build(arr, v + 1, tl, tm);
			build(arr, v + 2 * (tm - tl + 1), tm + 1, tr);
			tree[v] = combine(tree[v + 1], tree[v + 2 * (tm - tl + 1)]);
		}
	}
	node combine(const node& l, const node& r) const {
		vector<int> par(l.vals.size() + r.vals.size());
		merge(l.vals.begin(), L.vals.end(), r.vals.begin(), R.vals.end(), par.begin());
		return {par, l.l, r.r};
	}
	//How many of arr[l], arr[l+1], ..., arr[r] are < x?
	//O(log^2(n))
	int query(int l, int r, int x) const {
		return query(0, l, r, x);
	}
	int query(int v, int l, int r, int x) const {
		if (tree[v].r < l || r < tree[v].l)
			return 0;
		if (l <= tree[v].l && tree[v].r <= r) {
			const vector<int>& vals = tree[v].vals;
			return lower_bound(vals.begin(), vals.end(), x) - vals.begin();
		}
		return query(v + 1, l, r, x) +
		       query(v + tree[v].r_ch(), l, r, x);
	}
};
