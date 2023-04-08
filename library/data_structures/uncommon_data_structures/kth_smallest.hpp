/** @file */
#pragma once
/**
 * @see https://cp-algorithms.com/data_structures/segment_tree.html
 *     preserving-the-history-of-its-values-persistent-segment-tree
 */
struct kth_smallest {
	struct node {
		int sum;
		int lch, rch; /**< children, indexes into `tree` */
		node(int a_sum, int a_lch, int a_rch) : sum(a_sum), lch(a_lch), rch(a_rch) {}
	};
	/**
	 * calculated such that: mn <= arr[i] < mx
	 * @{
	 */
	int mn, mx;
	/** @} */
	vector<int> roots; /**< roots[i] corresponds to prefix arr[0, i) */
	deque<node> tree;
	/**
	 * @param arr static array; can't handle updates
	 * @time O(n log(mx - mn))
	 * @memory O(n log(mx - mn))
	 */
	kth_smallest(const vector<int>& arr) : roots(ssize(arr) + 1) {
		auto [mn_iter, mx_iter] = minmax_element(arr.begin(), arr.end());
		mn = *mn_iter, mx = *mx_iter + 1;
		tree.emplace_back(0, 0, 0); //acts as null
		for (int i = 0; i < ssize(arr); i++)
			roots[i + 1] = update_impl(arr[i], mn, mx, roots[i]);
	}
	int update_impl(int idx, int tl, int tr, int v) {
		if (tr - tl == 1) {
			tree.emplace_back(tree[v].sum + 1, 0, 0);
			return ssize(tree) - 1;
		}
		int tm = tl + (tr - tl) / 2;
		int lch = tree[v].lch;
		int rch = tree[v].rch;
		if (idx < tm)
			lch = update_impl(idx, tl, tm, lch);
		else
			rch = update_impl(idx, tm, tr, rch);
		tree.emplace_back(tree[lch].sum + tree[rch].sum, lch, rch);
		return ssize(tree) - 1;
	}
	/**
	 * @param le,ri defines range [le, ri)
	 * @param k query parameter
	 * @returns (k+1)th smallest number in range. k is 0-based, so
	 * query(le,ri,0) returns the min
	 * @time O(log(mx - mn))
	 */
	int query(int le, int ri, int k) const {
		assert(0 <= k && k < ri - le);
		assert(0 <= le && ri < ssize(roots));
		return query_impl(k, mn, mx, roots[le], roots[ri]);
	}
	int query_impl(int k, int tl, int tr, int vl, int vr) const {
		if (tr - tl == 1) return tl;
		int tm = tl + (tr - tl) / 2;
		int left_count = tree[tree[vr].lch].sum - tree[tree[vl].lch].sum;
		if (left_count > k) return query_impl(k, tl, tm, tree[vl].lch, tree[vr].lch);
		return query_impl(k - left_count, tm, tr, tree[vl].rch, tree[vr].rch);
	}
};
