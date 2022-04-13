#pragma once

struct persistentSegTree {

	struct Node {
		int lCh, rCh;//children, indexes into `tree`
		int sum;
		bool lazyTog;
	};

	int sz;
	deque<Node> tree;
	vector<int> roots;

	//implicit
	persistentSegTree(int _sz, int reserveSize) : sz(_sz) {
		//tree.reserve(reserveSize);
		tree.push_back({0, 0, 0, 0}); //acts as null
		tree.push_back({0, 0, 0, 0}); //root node
		roots.push_back(1);
	}

	void push(int v, int tl, int tr) {
		assert(v != 0);
		if (tree[v].lazyTog) {
			tree[v].sum = (tr - tl + 1) - tree[v].sum;
			tree[v].lazyTog = false;
			if (tl != tr) {
				assert(tree[v].lCh != 0);
				assert(tree[v].rCh != 0);
				tree[tree[v].lCh].lazyTog = !tree[tree[v].lCh].lazyTog;
				tree[tree[v].rCh].lazyTog = !tree[tree[v].rCh].lazyTog;
			}
		}
	}

	void toggleRange(int l, int r) {
		tree.push_back(tree[roots.back()]);//allocate top down
		roots.push_back(tree.size() - 1);
		toggleRange(roots.back(), 0, sz - 1, l, r);
	}
	void toggleRange(int v, int tl, int tr, int l, int r) {
		//allocate copies of previous children
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
			tree[v].sum = (tr - tl + 1) - tree[v].sum;
			if (tl != tr) {
				assert(lCh != 0);
				assert(rCh != 0);
				tree[lCh].lazyTog = !tree[lCh].lazyTog;
				tree[rCh].lazyTog = !tree[rCh].lazyTog;
			}
			return;
		}
		toggleRange(lCh, tl, tm, l, r);
		toggleRange(rCh, tm + 1, tr, l, r);
		tree[v].sum = tree[lCh].sum + tree[rCh].sum;
	}
};
