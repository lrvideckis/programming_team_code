#pragma once
//For point updates: either switch to policy based BST, or use sqrt decomposition
struct merge_sort_tree {
	const int N, S/*smallest power of 2 >= N*/;
	vector<vector<int>> tree;
	merge_sort_tree(const vector<int>& arr) : N(ssize(arr)),  S(N ? 1 << __lg(2 * N - 1) : 0), tree(2 * N) {
		for (int i = 0; i < N; i++)
			tree[i + N] = {arr[i]};
		rotate(tree.rbegin(), tree.rbegin() + S - N, tree.rbegin() + N);
		for (int i = N - 1; i >= 1; i--) {
			const auto& le = tree[2 * i];
			const auto& ri = tree[2 * i + 1];
			tree[i].reserve(ssize(le) + ssize(ri));
			merge(le.begin(), le.end(), ri.begin(), ri.end(), back_inserter(tree[i]));
		}
	}
	int value(int v, int x) const {
		return int(lower_bound(tree[v].begin(), tree[v].end(), x) - tree[v].begin());
	}
	int to_leaf(int i) const {
		i += S;
		return i < 2 * N ? i : 2 * (i - N);
	}
	/**
	 * Returns the number of values in range [le, ri) which are < x.
	 * @time O(log^2(n))
	 */
	int query(int le, int ri, int x) const {
		int res = 0;
		for (le = to_leaf(le), ri = to_leaf(ri); le < ri; le >>= 1, ri >>= 1) {
			if (le & 1) res += value(le++, x);
			if (ri & 1) res += value(--ri, x);
		}
		return res;
	}
};
