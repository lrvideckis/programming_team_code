#pragma once
//stress tests: tests/stress_tests/range_data_structures/distinct_query.cpp
//modified from https://cp-algorithms.com/data_structures/segment_tree.html#preserving-the-history-of-its-values-persistent-segment-tree
//works with negatives
//O(n log n) time and space
struct distinct_query {
	struct node {
		int sum;
		int l_ch, r_ch;//children, indexes into `tree`
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
		int l_ch = tree[v].l_ch;
		int r_ch = tree[v].r_ch;
		if (idx <= tm)
			l_ch = update(l_ch, tl, tm, idx);
		else
			r_ch = update(r_ch, tm + 1, tr, idx);
		tree.push_back({tree[l_ch].sum + tree[r_ch].sum, l_ch, r_ch});
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
		return query(tree[vl].l_ch, tree[vr].l_ch, tl, tm, idx) +
		       query(tree[vl].r_ch, tree[vr].r_ch, tm + 1, tr, idx);
	}
};
