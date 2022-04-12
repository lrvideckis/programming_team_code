#pragma once

//modified from https://cp-algorithms.com/data_structures/segment_tree.html#preserving-the-history-of-its-values-persistent-segment-tree
//tested on https://judge.yosupo.jp/problem/range_kth_smallest
struct kth_smallest {

	struct Node {
		int lCh, rCh;//children, indexes into `tree`
		int sum;
	};

	int sz;
	vector<Node> tree;
	vector<int> roots;

	kth_smallest(const vector<int>& arr) : sz(1e9 + 1 /*TODO: make sure it's > max(arr)*/) {
		tree.reserve(arr.size() * log(sz));
		tree.push_back({0, 0, 0}); //acts as null
		roots.push_back(0);
		for (int i = 0; i < (int)arr.size(); i++)
			roots.push_back(update(roots.back(), 0, sz - 1, arr[i], 1));
	}
	int update(int v, int tl, int tr, int idx, int diff) {
		if (tl == tr) {
			assert(tl == idx);
			tree.push_back({0, 0, tree[v].sum + diff});
			return tree.size() - 1;
		}
		int tm = (tl + tr) / 2;
		int lCh = tree[v].lCh;
		int rCh = tree[v].rCh;
		if (idx <= tm)
			lCh = update(lCh, tl, tm, idx, diff);
		else
			rCh = update(rCh, tm + 1, tr, idx, diff);
		tree.push_back({lCh, rCh, tree[lCh].sum + tree[rCh].sum});
		return tree.size() - 1;
	}


	/* find kth smallest number among arr[l], arr[l+1], ..., arr[r]
	 * k is 1-based, so find_kth(l,r,1) returns the min
	 * O(logn)
	 */
	int query(int l, int r, int k) const {
		assert(1 <= k && k <= r - l + 1); //note this condition implies L <= R
		assert(0 <= l && r < sz - 1);
		return query(roots[l], roots[r + 1], 0, sz - 1, k);
	}
	int query(int vl, int vr, int tl, int tr, int k) const {
		if (tl == tr)
			return tl;
		int tm = (tl + tr) / 2;
		int left_count = tree[tree[vr].lCh].sum - tree[tree[vl].lCh].sum;
		if (left_count >= k) return query(tree[vl].lCh, tree[vr].lCh, tl, tm, k);
		return query(tree[vl].rCh, tree[vr].rCh, tm + 1, tr, k - left_count);
	}
};
