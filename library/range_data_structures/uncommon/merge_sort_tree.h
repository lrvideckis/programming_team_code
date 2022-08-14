#pragma once
//For point updates: either switch to policy based BST, or use sqrt decomposition
struct merge_sort_tree {
	const int N, S/*smallest power of 2 >= N*/;
	vector<vector<int>> tree;
	//doesn't work with empty array
	merge_sort_tree(const vector<int>& arr) : N(ssize(arr)), S(1 << __lg(2 * N - 1)), tree(2 * N) {
		for (int i = 0; i < N; i++)
			tree[i + N] = {arr[i]};
		rotate(tree.rbegin(), tree.rbegin() + S - N, tree.rbegin() + N);
		for (int i = N - 1; i >= 1; i--) {
			const auto& l = tree[2 * i];
			const auto& r = tree[2 * i + 1];
			tree[i].reserve(ssize(l) + ssize(r));
			merge(l.begin(), l.end(), r.begin(), r.end(), back_inserter(tree[i]));
		}
	}
	int value(int v, int x) const {
		return lower_bound(tree[v].begin(), tree[v].end(), x) - tree[v].begin();
	}
	int to_leaf(int i) const {
		i += S;
		return i < 2 * N ? i : 2 * (i - N);
	}
	//How many values in range [l, r) are < x?
	//O(log^2(n))
	int query(int l, int r, int x) const {
		int res = 0;
		for (l = to_leaf(l), r = to_leaf(r); l < r; l >>= 1, r >>= 1) {
			if (l & 1) res += value(l++, x);
			if (r & 1) res += value(--r, x);
		}
		return res;
	}
};
