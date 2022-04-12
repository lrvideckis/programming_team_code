#pragma once

//modified from https://cp-algorithms.com/data_structures/segment_tree.html#preserving-the-history-of-its-values-persistent-segment-tree
//tested on https://www.spoj.com/problems/DQUERY/
struct persistentSegTree {

	struct Node {
		int lCh, rCh;//children, indexes into `tree`
		int sum;
	};

	int sz;
	vector<Node> tree;
	vector<int> roots;

	persistentSegTree(const vector<int>& arr) : sz(arr.size() + 1) {
		tree.reserve(sz * log(sz));
		tree.push_back({0, 0, 0}); //acts as null
		roots.push_back(0);
		unordered_map<int, int> lastIdx;
		for (int i = 0; i < (int)arr.size(); i++) {
			roots.push_back(update(roots.back(), 0, sz - 1, lastIdx[arr[i]], 1));
			lastIdx[arr[i]] = i + 1;
		}
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

	//returns number of distinct elements in range [l,r]
	int query(int l, int r) const {
		return query(roots[l], roots[r + 1], 0, sz - 1, l + 1);
	}
	int query(int vl, int vr, int tl, int tr, int idx) const {
		if (tree[vr].sum == 0 || idx <= tl)
			return 0;
		if (tr < idx)
			return tree[vr].sum - tree[vl].sum;
		int tm = (tl + tr) / 2;
		return query(tree[vl].lCh, tree[vr].lCh, tl, tm, idx) +
		       query(tree[vl].rCh, tree[vr].rCh, tm + 1, tr, idx);
	}
};
