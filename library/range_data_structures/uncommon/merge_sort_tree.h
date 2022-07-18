#pragma once
//library checker tests: https://judge.yosupo.jp/problem/static_range_frequency, https://judge.yosupo.jp/problem/range_kth_smallest
//For point updates: either switch to policy based BST, or use sqrt decomposition
struct merge_sort_tree {
	struct node {
		vector<int> val; //sorted list of values
		int l, r;
	};
	vector<node> tree;
	//RTE's when `arr` is empty
	merge_sort_tree(const vector<int>& arr) : tree(4 * arr.size()) {
		build(arr, 1, 0, arr.size());
	}
	void build(const vector<int>& arr, int v, int tl, int tr) {
		if (tr - tl == 1) {
			tree[v] = {
				{arr[tl]},
				tl,
				tr
			};
		} else {
			int tm = tl + (tr - tl) / 2;
			build(arr, 2 * v, tl, tm);
			build(arr, 2 * v + 1, tm, tr);
			const auto& l = tree[2 * v].val;
			const auto& r = tree[2 * v + 1].val;
			merge(l.begin(), l.end(), r.begin(), r.end(), back_inserter(tree[v].val));
			tree[v].l = tl, tree[v].r = tr;
		}
	}
	//How many values in range [l, r) are < x?
	//O(log^2(n))
	int query(int l, int r, int x) {
		return query(1, l, r, x);
	}
	int query(int v, int l, int r, int x) {
		if (r <= tree[v].l || tree[v].r <= l)
			return 0;
		if (l <= tree[v].l && tree[v].r <= r) {
			const vector<int>& val = tree[v].val;
			return lower_bound(val.begin(), val.end(), x) - val.begin();
		}
		return query(2 * v, l, r, x) +
		       query(2 * v + 1, l, r, x);
	}
};
