#pragma once
/**
 * Can't handle updates.
 * @see https://cp-algorithms.com/data_structures/segment_tree.html
 *     preserving-the-history-of-its-values-persistent-segment-tree
 */
struct kth_smallest {
	struct node {
		int sum;
		int lch, rch;//children, indexes into `tree`
		node(int a_sum, int a_lch, int a_rch) : sum(a_sum), lch(a_lch), rch(a_rch) {}
	};
	int mn, mx;
	vector<int> roots;
	deque<node> tree;
	/**
	 * @time O(n log max)
	 * @memory O(n log max)
	 */
	kth_smallest(const vector<int>& arr) : roots(ssize(arr) + 1, 0) {
		auto [mn_iter, mx_iter] = minmax_element(arr.begin(), arr.end());
		mn = *mn_iter, mx = *mx_iter + 1;
		tree.emplace_back(0, 0, 0); //acts as null
		transform(arr.begin(), arr.end(), roots.begin(), roots.begin() + 1, [&](int val, int root) {
			return update(root, mn, mx, val);
		});
	}
	int update(int v, int tl, int tr, int idx) {
		if (tr - tl == 1) {
			tree.emplace_back(tree[v].sum + 1, 0, 0);
			return ssize(tree) - 1;
		}
		int tm = tl + (tr - tl) / 2;
		int lch = tree[v].lch;
		int rch = tree[v].rch;
		if (idx < tm) lch = update(lch, tl, tm, idx);
		else rch = update(rch, tm, tr, idx);
		tree.emplace_back(tree[lch].sum + tree[rch].sum, lch, rch);
		return ssize(tree) - 1;
	}
	/**
	 * Returns (k+1)th smallest number in range [le, ri). k is 0-based, so
	 * query(le,ri,0) returns the min; query(le,ri,ri-le-1) returns the max.
	 * @time O(log max)
	 */
	int query(int le, int ri, int k) const {
		assert(0 <= k && k < ri - le); //note this condition implies le < ri
		assert(0 <= le && ri < ssize(roots));
		return query(roots[le], roots[ri], mn, mx, k);
	}
	int query(int vl, int vr, int tl, int tr, int k) const {
		assert(tree[vr].sum > tree[vl].sum);
		if (tr - tl == 1) return tl;
		int tm = tl + (tr - tl) / 2;
		int left_count = tree[tree[vr].lch].sum - tree[tree[vl].lch].sum;
		if (left_count > k) return query(tree[vl].lch, tree[vr].lch, tl, tm, k);
		return query(tree[vl].rch, tree[vr].rch, tm, tr, k - left_count);
	}
};
