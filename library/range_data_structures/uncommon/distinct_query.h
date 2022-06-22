#pragma once
//stress tests: tests/stress_tests/range_data_structures/distinct_query.cpp
//source: https://cp-algorithms.com/data_structures/segment_tree.html#preserving-the-history-of-its-values-persistent-segment-tree
//works with negatives
//O(n log n) time and space
struct distinct_query {
	struct node {
		int sum;
		int lch, rch;//children, indexes into `tree`
	};
	vector<int> roots;
	deque<node> tree;
	distinct_query(const vector<int>& arr) : roots(arr.size() + 1, 0) {
		tree.push_back({0, 0, 0}); //acts as null
		map<int, int> last_idx;
		for (int i = 0; i < (int)arr.size(); i++) {
			roots[i + 1] = update(roots[i], 0, arr.size(), last_idx[arr[i]]);
			last_idx[arr[i]] = i + 1;
		}
	}
	int update(int v, int tl, int tr, int idx) {
		if (tl == tr) {
			tree.push_back({tree[v].sum + 1, 0, 0});
			return tree.size() - 1;
		}
		int tm = (tl + tr) / 2;
		int lch = tree[v].lch;
		int rch = tree[v].rch;
		if (idx <= tm)
			lch = update(lch, tl, tm, idx);
		else
			rch = update(rch, tm + 1, tr, idx);
		tree.push_back({tree[lch].sum + tree[rch].sum, lch, rch});
		return tree.size() - 1;
	}
	//returns number of distinct elements in range [l,r]
	int query(int l, int r) const {
		return query(roots[l], roots[r + 1], 0, (int)roots.size() - 1, l + 1);
	}
	int query(int vl, int vr, int tl, int tr, int idx) const {
		if (tree[vr].sum == 0 || idx <= tl)
			return 0;
		if (tr < idx)
			return tree[vr].sum - tree[vl].sum;
		int tm = (tl + tr) / 2;
		return query(tree[vl].lch, tree[vr].lch, tl, tm, idx) +
		       query(tree[vl].rch, tree[vr].rch, tm + 1, tr, idx);
	}
};
