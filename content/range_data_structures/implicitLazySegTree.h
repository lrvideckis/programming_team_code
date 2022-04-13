#pragma once

//status: tested on https://codeforces.com/contest/52/problem/C

struct implicitLazySegTree {

	struct Node {
		int lCh, rCh;//children, indexes into `tree`
		ll mn;
		ll lazyAdd;
	};

	int sz;
	deque<Node> tree;

	implicitLazySegTree(int _sz) : sz(_sz) {
		tree.push_back({0, 0, 0, 0}); //acts as null
		tree.push_back({0, 0, 0, 0}); //root node
	}

	void push(int v, int tl, int tr) {
		assert(v != 0);
		if (tl != tr && tree[v].lCh == 0) {
			tree.push_back(tree[0]);
			tree[v].lCh = tree.size() - 1;
			tree.push_back(tree[0]);
			tree[v].rCh = tree.size() - 1;
		}
		if (tree[v].lazyAdd) {
			tree[v].mn += tree[v].lazyAdd;
			if (tl != tr) {
				assert(tree[v].lCh != 0);//need to push lazy to childs, else incorrect
				assert(tree[v].rCh != 0);
				tree[tree[v].lCh].lazyAdd += tree[v].lazyAdd;
				tree[tree[v].rCh].lazyAdd += tree[v].lazyAdd;
			}
			tree[v].lazyAdd = 0;
		}
	}

	//add diff to each value in range [l,r]
	void update(int l, int r, ll diff) {
		update(1, 0, sz - 1, l, r, diff);
	}
	void update(int v, int tl, int tr, int l, int r, ll diff) {
		push(v, tl, tr);
		if (tr < l || r < tl)
			return;
		int tm = (tl + tr) / 2;
		int lCh = tree[v].lCh;
		int rCh = tree[v].rCh;
		if (l <= tl && tr <= r) {
			tree[v].mn += diff;
			if (tl != tr) {
				assert(lCh != 0);
				assert(rCh != 0);
				tree[lCh].lazyAdd += diff;
				tree[rCh].lazyAdd += diff;
			}
			return;
		}
		update(lCh, tl, tm, l, r, diff);
		update(rCh, tm + 1, tr, l, r, diff);
		tree[v].mn = min(tree[lCh].mn, tree[rCh].mn);
	}

	//min on range [l,r]
	ll query(int l, int r) {
		return query(1, 0, sz - 1, l, r);
	}
	ll query(int v, int tl, int tr, int l, int r) {
		push(v, tl, tr);
		if (tr < l || r < tl)
			return 1e18;
		if (l <= tl && tr <= r)
			return tree[v].mn;
		int tm = (tl + tr) / 2;
		return min(query(tree[v].lCh, tl, tm, l, r),
		           query(tree[v].rCh, tm + 1, tr, l, r));
	}
};
