#pragma once
//stress tests: tests/stress-tests/range_data_structures/distinct_query.cpp

//modified from https://cp-algorithms.com/data_structures/segment_tree.html#preserving-the-history-of-its-values-persistent-segment-tree

//works with negatives
//O(n log n) time and space

struct distinct_query {

	struct Node {
		int sum;
		int lCh, rCh;//children, indexes into `tree`
	};

	int sz;
	deque<Node> tree;
	vector<int> roots;

	distinct_query(const vector<int>& arr) : sz(arr.size() + 1) {
		tree.push_back({0, 0, 0}); //acts as null
		roots.push_back(0);
		map<int, int> lastIdx;
		for (int i = 0; i < (int)arr.size(); i++) {
			roots.push_back(update(roots.back(), 0, sz - 1, lastIdx[arr[i]]));
			lastIdx[arr[i]] = i + 1;
		}
	}
	int update(int v, int tl, int tr, int idx) {
		if (tl == tr) {
			tree.push_back({tree[v].sum + 1, 0, 0});
			return tree.size() - 1;
		}
		int tm = (tl + tr) / 2;
		int lCh = tree[v].lCh;
		int rCh = tree[v].rCh;
		if (idx <= tm)
			lCh = update(lCh, tl, tm, idx);
		else
			rCh = update(rCh, tm + 1, tr, idx);
		tree.push_back({tree[lCh].sum + tree[rCh].sum, lCh, rCh});
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
