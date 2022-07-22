#pragma once
//For point updates: either switch to policy based BST, or use sqrt decomposition
struct merge_sort_tree {
	const int n;
	struct node {
		vector<int> val;
		int l, r;//[l, r)
	};
	vector<node> tree;
	//RTE's when `arr` is empty
	merge_sort_tree(const vector<int>& arr) : n(arr.size()), tree(2 * n) {
		for (int i = 0, j = 1 << __lg(2 * n - 1); i < n; i++, j = (j + 1) % n + n)
			tree[j] = {{arr[i]}, i, i + 1};
		for (int i = n - 1; i >= 1; i--) {
			const auto& l = tree[2 * i].val;
			const auto& r = tree[2 * i + 1].val;
			merge(l.begin(), l.end(), r.begin(), r.end(), back_inserter(tree[i].val));
			tree[i].l = tree[2 * i].l;
			tree[i].r = tree[2 * i + 1].r;
		}
	}
	int num_less(int v, int x) const {
		const vector<int>& val = tree[v].val;
		return lower_bound(val.begin(), val.end(), x) - val.begin();
	}
	int range_idx(int i) const {
		i += 1 << __lg(2 * n - 1);
		return i < 2 * n ? i : 2 * (i - n);
	}
	//How many values in range [l, r) are < x?
	//O(log^2(n))
	int query(int l, int r, int x) const {
		l = range_idx(l), r = range_idx(r);
		int res = 0;
		for (; l < r; l >>= 1, r >>= 1) {
			if (l & 1) res += num_less(l++, x);
			if (r & 1) res += num_less(--r, x);
		}
		return res;
	}
	int query(int v/* = 1*/, int l, int r, int x) const {
		if (r <= tree[v].l || tree[v].r <= l)
			return 0;
		if (l <= tree[v].l && tree[v].r <= r)
			return num_less(v, x);
		return query(2 * v, l, r, x) +
		       query(2 * v + 1, l, r, x);
	}
};
