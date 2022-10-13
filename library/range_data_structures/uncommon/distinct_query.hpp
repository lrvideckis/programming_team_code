#pragma once
//source: https://cp-algorithms.com/data_structures/segment_tree.html
//	#preserving-the-history-of-its-values-persistent-segment-tree
//works with negatives
//O(n log n) time and space
struct distinct_query {
	struct node {
		int sum;
		int lch, rch;//children, indexes into `tree`
		node(int a_sum, int a_lch, int a_rch) : sum(a_sum), lch(a_lch), rch(a_rch) {}
	};
	const int N;
	vector<int> roots;
	deque<node> tree;
	distinct_query(const vector<int>& arr) : N(ssize(arr)), roots(N + 1, 0) {
		tree.emplace_back(0, 0, 0); //acts as null
		map<int, int> last_idx;
		for (int i = 0; i < N; i++) {
			roots[i + 1] = update(roots[i], 0, N, last_idx[arr[i]]);
			last_idx[arr[i]] = i + 1;
		}
	}
	int update(int v, int tl, int tr, int idx) {
		if (tr - tl == 1) {
			tree.emplace_back(tree[v].sum + 1, 0, 0);
			return ssize(tree) - 1;
		}
		int tm = tl + (tr - tl) / 2;
		int lch = tree[v].lch;
		int rch = tree[v].rch;
		if (idx < tm)
			lch = update(lch, tl, tm, idx);
		else
			rch = update(rch, tm, tr, idx);
		tree.emplace_back(tree[lch].sum + tree[rch].sum, lch, rch);
		return ssize(tree) - 1;
	}
	//returns number of distinct elements in range [le,ri)
	int query(int le, int ri) const {
		assert(0 <= le && le <= ri && ri <= N);
		return query(roots[le], roots[ri], 0, N, le + 1);
	}
	int query(int vl, int vr, int tl, int tr, int idx) const {
		if (tree[vr].sum == 0 || idx <= tl)
			return 0;
		if (tr <= idx)
			return tree[vr].sum - tree[vl].sum;
		int tm = tl + (tr - tl) / 2;
		return query(tree[vl].lch, tree[vr].lch, tl, tm, idx) +
		       query(tree[vl].rch, tree[vr].rch, tm, tr, idx);
	}
};
