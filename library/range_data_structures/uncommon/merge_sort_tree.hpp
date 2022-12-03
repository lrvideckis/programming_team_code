/** @file */
#pragma once
/**
 * For point updates: either switch to policy based BST, or use sqrt
 * decomposition.
 */
struct merge_sort_tree {
	const int N, S /**< smallest power of 2 >= N */;
	vector<vector<int>> tree;
	/**
	 * @param arr static array
	 */
	merge_sort_tree(const vector<int>& arr) : N(ssize(arr)),  S(N ? 1 << __lg(2 * N - 1) : 0), tree(2 * N) {
		transform(arr.begin(), arr.end(), tree.begin() + N, [](int val) -> vector<int> {
			return {val};
		});
		rotate(tree.rbegin(), tree.rbegin() + S - N, tree.rbegin() + N);
		for (int i = N - 1; i >= 1; i--) {
			const auto& le = tree[2 * i];
			const auto& ri = tree[2 * i + 1];
			tree[i].resize(ssize(le) + ssize(ri));
			merge(le.begin(), le.end(), ri.begin(), ri.end(), tree[i].begin());
		}
	}
	/**
	 * @param v a node
	 * @param x target value
	 * @returns number of values equal to x in v's corresponding array
	 * @time O(log n)
	 */
	int value(int v, int x) const {
		auto [le, ri] = equal_range(tree[v].begin(), tree[v].end(), x);
		return int(ri - le);
	}
	/**
	 * @param i endpoint of subarray of arr
	 * @returns corresponding leaf index
	 */
	int to_leaf(int i) const {
		i += S;
		return i < 2 * N ? i : 2 * (i - N);
	}
	/**
	 * @param le,ri defines range [le, ri)
	 * @param x query parameter
	 * @returns the number of values in range equal to x.
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
