#pragma once
//library checker tests: https://judge.yosupo.jp/problem/range_kth_smallest
//modified from https://cp-algorithms.com/data_structures/segment_tree.html#preserving-the-history-of-its-values-persistent-segment-tree
struct kth_smallest {
	struct node {
		int sum;
		int l_ch, r_ch;//children, indexes into `tree`
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
		int l_ch = tree[v].l_ch;
		int r_ch = tree[v].r_ch;
		if (idx <= tm)
			l_ch = update(l_ch, tl, tm, idx);
		else
			r_ch = update(r_ch, tm + 1, tr, idx);
		tree.push_back({tree[l_ch].sum + tree[r_ch].sum, l_ch, r_ch});
		return tree.size() - 1;
	}
	/* find (k+1)th smallest number among arr[l], arr[l+1], ..., arr[r]
	 * k is 0-based, so query(l,r,0) returns the min
	 */
	int query(int l, int r, int k) const {
		assert(0 <= k && k < r - l + 1); //note this condition implies L <= R
		assert(0 <= l && r + 1 < (int)roots.size());
		return query(roots[l], roots[r + 1], mn, mx, k);
	}
	int query(int vl, int vr, int tl, int tr, int k) const {
		if (tl == tr)
			return tl;
		int tm = tl + (tr - tl) / 2;
		int left_count = tree[tree[vr].l_ch].sum - tree[tree[vl].l_ch].sum;
		if (left_count > k) return query(tree[vl].l_ch, tree[vr].l_ch, tl, tm, k);
		return query(tree[vl].r_ch, tree[vr].r_ch, tm + 1, tr, k - left_count);
	}
};
