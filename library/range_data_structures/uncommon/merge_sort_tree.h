#pragma once
//For point updates: either switch to policy based BST, or use sqrt decomposition
struct merge_sort_tree {
	const int N;
	vector<vector<int>> tree;
	//RTE's when `arr` is empty
	merge_sort_tree(const vector<int>& arr) : N(arr.size()), tree(2 * N) {
		for (int i = 0, j = 1 << __lg(2 * N - 1); i < N; i++, j = (j + 1) % N + N)
			tree[j] = {arr[i]};
		for (int i = N - 1; i >= 1; i--) {
			const auto& l = tree[2 * i];
			const auto& r = tree[2 * i + 1];
			merge(l.begin(), l.end(), r.begin(), r.end(), back_inserter(tree[i]));
		}
	}
	int value(int v, int x) const {
		const vector<int>& val = tree[v];
		return lower_bound(val.begin(), val.end(), x) - val.begin();
	}
	int range_idx(int i) const {
		i += 1 << __lg(2 * N - 1);
		return i < 2 * N ? i : 2 * (i - N);
	}
	//How many values in range [l, r) are < x?
	//O(log^2(n))
	int query(int l, int r, int x) const {
		l = range_idx(l), r = range_idx(r);
		int res = 0;
		for (; l < r; l >>= 1, r >>= 1) {
			if (l & 1) res += value(l++, x);
			if (r & 1) res += value(--r, x);
		}
		return res;
	}
};
