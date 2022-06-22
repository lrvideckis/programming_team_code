#pragma once
//library checker tests: https://judge.yosupo.jp/problem/range_kth_smallest
//source: https://cp-algorithms.com/data_structures/segment_tree.html#preserving-the-history-of-its-values-persistent-segment-tree
struct kth_smallest {
	struct node {
		int sum;
		int lch, rch;//children, indexes into `tree`
	};
	int mn, mx;
	vector<int> roots;
	deque<node> tree;
	kth_smallest(const vector<int>& arr) : mn(INT_MAX), mx(INT_MIN), roots(arr.size() + 1, 0) {
		tree.push_back({0, 0, 0}); //acts as null
		for (int val : arr) mn = min(mn, val), mx = max(mx, val);
		for (int i = 0; i < (int)arr.size(); i++)
			roots[i + 1] = update(roots[i], mn, mx, arr[i]);
	}
	int update(int v, int tl, int tr, int idx) {
		if (tl == tr) {
			tree.push_back({tree[v].sum + 1, 0, 0});
			return tree.size() - 1;
		}
		int tm = tl + (tr - tl) / 2;
		int lch = tree[v].lch;
		int rch = tree[v].rch;
		if (idx <= tm)
			lch = update(lch, tl, tm, idx);
		else
			rch = update(rch, tm + 1, tr, idx);
		tree.push_back({tree[lch].sum + tree[rch].sum, lch, rch});
		return tree.size() - 1;
	}
	/* find (k+1)th smallest number among arr[l], arr[l+1], ..., arr[r]
	 * k is 0-based, so query(l,r,0) returns the min
	 */
	int query(int l, int r, int k) const {
		assert(0 <= k && k < r - l + 1); //note this condition implies l <= r
		assert(0 <= l && r + 1 < (int)roots.size());
		return query(roots[l], roots[r + 1], mn, mx, k);
	}
	int query(int vl, int vr, int tl, int tr, int k) const {
		if (tl == tr)
			return tl;
		int tm = tl + (tr - tl) / 2;
		int left_count = tree[tree[vr].lch].sum - tree[tree[vl].lch].sum;
		if (left_count > k) return query(tree[vl].lch, tree[vr].lch, tl, tm, k);
		return query(tree[vl].rch, tree[vr].rch, tm + 1, tr, k - left_count);
	}
};
