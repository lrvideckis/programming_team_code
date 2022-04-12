#pragma once

//modified from https://cp-algorithms.com/data_structures/segment_tree.html#preserving-the-history-of-its-values-persistent-segment-tree
//tested on https://www.spoj.com/problems/PSEGTREE/ and https://cses.fi/problemset/task/1737/
struct persistentSegTree {

	struct Node {
		int lCh, rCh;//children, indexes into `tree`
		ll sum;
	};

	int sz;
	vector<Node> tree;
	vector<int> roots;

	//implicit
	persistentSegTree(int _sz, int reserveSize) : sz(_sz) {
		tree.reserve(reserveSize);
		tree.push_back({0, 0, 0LL}); //acts as null
		roots.push_back(0);
	}

	persistentSegTree(const vector<ll>& arr) : sz(arr.size()) {
		tree.reserve(4 * sz);
		tree.push_back({0, 0, 0LL}); //acts as null
		roots.push_back(build(arr, 0, sz - 1));
	}
	int build(const vector<ll>& arr, int tl, int tr) {
		if (tl == tr) {
			tree.push_back({0, 0, arr[tl]});
			return tree.size() - 1;
		}
		int tm = (tl + tr) / 2;
		int lCh = build(arr, tl, tm);
		int rCh = build(arr, tm + 1, tr);
		tree.push_back({lCh, rCh, tree[lCh].sum + tree[rCh].sum});
		return tree.size() - 1;
	}

	void update(int version, int idx, ll diff) {
		roots.push_back(update(roots[version], 0, sz - 1, idx, diff));
	}
	int update(int v, int tl, int tr, int idx, ll diff) {
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

	ll query(int version, int l, int r) const {
		return query(roots[version], 0, sz - 1, l, r);
	}
	ll query(int v, int tl, int tr, int l, int r) const {
		if (tree[v].sum == 0LL || tr < l || r < tl)
			return 0LL;
		if (l <= tl && tr <= r)
			return tree[v].sum;
		int tm = (tl + tr) / 2;
		return query(tree[v].lCh, tl, tm, l, r) +
		       query(tree[v].rCh, tm + 1, tr, l, r);
	}
};
