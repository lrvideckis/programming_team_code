#pragma once

struct persistentLazySegTree {

	struct Node {
		int lCh, rCh;//children, indexes into `tree`
		long long mn;
		long long lazyAdd;
	};

	int sz;
	deque<Node> tree;
	vector<int> roots;

	//implicit
	persistentLazySegTree(int _sz) : sz(_sz) {
		tree.push_back({0, 0, 0, 0}); //acts as null
		roots.push_back(0);
	}

	void push(int v, int tl, int tr) {
		if (tree[v].lazyAdd) {
			tree[v].mn += tree[v].lazyAdd;
			if (tl != tr) {
				if (tree[v].lCh != 0) tree[tree[v].lCh].lazyAdd += tree[v].lazyAdd;
				if (tree[v].rCh != 0) tree[tree[v].rCh].lazyAdd += tree[v].lazyAdd;
			}
			tree[v].lazyAdd = 0;
		}
	}

	//add diff to each value in range [l,r]
	void update(int l, int r, long long diff) {
		tree.push_back(tree[roots.back()]);//allocate top down
		roots.push_back(tree.size() - 1);
		update(roots.back(), 0, sz - 1, l, r, diff);
	}
	void update(int v, int tl, int tr, int l, int r, long long diff) {
		//allocate copies of previous version's children
		if (tl != tr) {
			tree.push_back(tree[tree[v].lCh]);
			tree[v].lCh = tree.size() - 1;
			tree.push_back(tree[tree[v].rCh]);
			tree[v].rCh = tree.size() - 1;
		}
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

	//min on range [l,r] for most recent version
	long long query(int l, int r) {
		return query(roots.back(), 0, sz - 1, l, r);
	}
	long long query(int v, int tl, int tr, int l, int r) {
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
