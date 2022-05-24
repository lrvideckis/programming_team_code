#pragma once
//library checker tests: https://judge.yosupo.jp/problem/range_kth_smallest

//modified from https://cp-algorithms.com/data_structures/segment_tree.html#preserving-the-history-of-its-values-persistent-segment-tree
//works for -1e9 <= arr[i] <= 1e9

struct kth_smallest {

	const int mx = 1e9;

	struct Node {
		int sum;
		int lCh, rCh;//children, indexes into `tree`
	};

	deque<Node> tree;
	vector<int> roots;

	kth_smallest(const vector<int>& arr) {
		tree.push_back({0, 0, 0}); //acts as null
		roots.push_back(0);
		for (int i = 0; i < (int)arr.size(); i++) {
			assert(-mx <= arr[i] && arr[i] <= mx);
			roots.push_back(update(roots.back(), -mx, mx, arr[i]));
		}
	}
	int update(int v, int tl, int tr, int idx) {
		if (tl == tr) {
			tree.push_back({tree[v].sum + 1, 0, 0});
			return tree.size() - 1;
		}
		int tm = tl + (tr - tl) / 2;
		int lCh = tree[v].lCh;
		int rCh = tree[v].rCh;
		if (idx <= tm)
			lCh = update(lCh, tl, tm, idx);
		else
			rCh = update(rCh, tm + 1, tr, idx);
		tree.push_back({tree[lCh].sum + tree[rCh].sum, lCh, rCh});
		return tree.size() - 1;
	}


	/* find kth smallest number among arr[l], arr[l+1], ..., arr[r]
	 * k is 1-based, so find_kth(l,r,1) returns the min
	 */
	int query(int l, int r, int k) const {
		assert(1 <= k && k <= r - l + 1); //note this condition implies L <= R
		assert(0 <= l && r + 1 < (int)roots.size());
		return query(roots[l], roots[r + 1], -mx, mx, k);
	}
	int query(int vl, int vr, int tl, int tr, int k) const {
		if (tl == tr)
			return tl;
		int tm = tl + (tr - tl) / 2;
		int left_count = tree[tree[vr].lCh].sum - tree[tree[vl].lCh].sum;
		if (left_count >= k) return query(tree[vl].lCh, tree[vr].lCh, tl, tm, k);
		return query(tree[vl].rCh, tree[vr].rCh, tm + 1, tr, k - left_count);
	}
};
