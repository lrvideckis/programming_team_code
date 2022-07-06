#pragma once
//library checker tests: https://judge.yosupo.jp/problem/static_range_frequency, https://judge.yosupo.jp/problem/range_kth_smallest
//For point updates: either switch to policy based BST, or use sqrt decomposition
struct merge_sort_tree {
	struct node {
		vector<int> val; //sorted list of values
		int l, r;
		//returns 1 + (# of nodes in left child's subtree)
		//https://cp-algorithms.com/data_structures/segment_tree.html#memory-efficient-implementation
		int rch() const { //right child
			return (r - l + 2) & ~1;
		}
	};
	vector<node> tree;
	//RTE's when `arr` is empty
	merge_sort_tree(const vector<int>& arr) : tree(2 * (int)arr.size() - 1) {
		int timer = 0;
		build(arr, timer, 0, (int)arr.size() - 1);
	}
	vector<int> build(const vector<int>& arr, int& timer, int tl, int tr) {
		node& curr = tree[timer++];
		if (tl == tr) {
			curr.val = {arr[tl]};
		} else {
			int tm = tl + (tr - tl) / 2;
			const vector<int>& l = build(arr, timer, tl, tm);
			const vector<int>& r = build(arr, timer, tm + 1, tr);
			merge(l.begin(), l.end(), r.begin(), r.end(), back_inserter(curr.val));
		}
		curr.l = tl, curr.r = tr;
		return curr.val;
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
			const vector<int>& val = tree[v].val;
			return lower_bound(val.begin(), val.end(), x) - val.begin();
		}
		return query(v + 1, l, r, x) +
		       query(v + tree[v].rch(), l, r, x);
	}
};
