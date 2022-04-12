#pragma once

//status: tested on https://cses.fi/problemset/task/1144/ and https://judge.yosupo.jp/problem/point_add_range_sum

struct implicitSegTree {
	struct Node {
		int lCh, rCh;//children ptrs, indexes into `tree`; 0 for null
		ll sum;
	};

	int sz;
	vector<Node> tree;

	implicitSegTree(int _sz, int reserveAmount): sz(_sz) {
		tree.reserve(reserveAmount);
		tree.push_back({0, 0, 0LL});//acts as null
		tree.push_back({0, 0, 0LL});//root node
	}

	void update(int idx, ll diff) {
		update(1, 0, sz - 1, idx, diff);
	}
	int update(int v, int tl, int tr, int idx, ll diff) {
		if (tl == tr) {
			if (v == 0) {
				tree.push_back(tree[0]);
				v = tree.size() - 1;
			}
			tree[v].sum += diff;
			return v;
		}
		int tm = (tl + tr) / 2;
		int lCh = tree[v].lCh;
		int rCh = tree[v].rCh;
		if (idx <= tm)
			lCh = update(lCh, tl, tm, idx, diff);
		else
			rCh = update(rCh, tm + 1, tr, idx, diff);
		if (v == 0) {
			tree.push_back(tree[0]);
			v = tree.size() - 1;
		}
		tree[v] = {lCh, rCh, tree[lCh].sum + tree[rCh].sum};
		return v;
	}

	//inclusive range: [l,r]
	ll query(int l, int r) const {
		return query(1, 0, sz - 1, l, r);
	}
	ll query(int v, int tl, int tr, int l, int r) const {
		if (tree[v].sum == 0LL || tr < l || r < tl) return 0LL;
		if (l <= tl && tr <= r) return tree[v].sum;
		int tm = (tl + tr) / 2;
		return query(tree[v].lCh, tl, tm, l, r) +
		       query(tree[v].rCh, tm + 1, tr, l, r);
	}
};
