#pragma once
//status: not tested

struct persistentLazySegTree {

	struct Node {
		int lCh, rCh;//children, indexes into `tree`
		int sum;
		bool lazyTog;
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
		if (tl != tr) {
			tree.push_back(tree[tree[v].lCh]);
			tree[v].lCh = tree.size() - 1;
			tree.push_back(tree[tree[v].rCh]);
			tree[v].rCh = tree.size() - 1;
		}
		if (tree[v].lazyTog) {
			tree[v].sum = (tr - tl + 1) - tree[v].sum;
			tree[v].lazyTog = false;
			if (tl != tr) {
				tree[tree[v].lCh].lazyTog ^= 1;
				tree[tree[v].rCh].lazyTog ^= 1;
			}
		}
	}

	void set(int idx, int new_val) {
		tree.push_back(tree[roots.back()]);//allocate top down
		roots.push_back(tree.size() - 1);
		set(roots.back(), 0, sz - 1, idx, new_val);
	}
	void set(int v, int tl, int tr, int idx, int new_val) {
		push(v, tl, tr);
		if (tr < idx || idx < tl)
			return;
		if (idx <= tl && tr <= idx) {
			tree[v].sum = new_val;
			return;
		}
		int tm = (tl + tr) / 2;
		int lCh = tree[v].lCh;
		int rCh = tree[v].rCh;
		set(lCh, tl, tm, idx, new_val);
		set(rCh, tm + 1, tr, idx, new_val);
		tree[v].sum = tree[lCh].sum + tree[rCh].sum;
	}

	void toggleRange(int l, int r) {
		tree.push_back(tree[roots.back()]);//allocate top down
		roots.push_back(tree.size() - 1);
		toggleRange(roots.back(), 0, sz - 1, l, r);
	}
	void toggleRange(int v, int tl, int tr, int l, int r) {
		push(v, tl, tr);
		if (tr < l || r < tl)
			return;
		int lCh = tree[v].lCh;
		int rCh = tree[v].rCh;
		if (l <= tl && tr <= r) {
			tree[v].sum = (tr - tl + 1) - tree[v].sum;
			if (tl != tr) {
				tree[lCh].lazyTog ^= 1;
				tree[rCh].lazyTog ^= 1;
			}
			return;
		}
		int tm = (tl + tr) / 2;
		toggleRange(lCh, tl, tm, l, r);
		toggleRange(rCh, tm + 1, tr, l, r);
		tree[v].sum = tree[lCh].sum + tree[rCh].sum;
	}

	//let's use implementation trick described here https://codeforces.com/blog/entry/72626
	//so that we don't have to propagate lazy vals and thus we don't have to allocate new nodes
	int query(int l, int r) const {
		int version = roots.size() - 1;
		int root = roots[version];
		return query(root, 0, sz - 1, l, r, tree[root].lazyTog);
	}
	int query(int v, int tl, int tr, int l, int r, bool tog) const {
		if (v == 0 || tr < l || r < tl)
			return 0;
		if (l <= tl && tr <= r) {
			int sum = tree[v].sum;
			if (tree[v].lazyTog) sum = (tr - tl + 1) - sum;
			return sum;
		}
		int tm = (tl + tr) / 2;
		tog ^= tree[v].lazyTog;
		return query(tree[v].lCh, tl, tm, l, r, tog) +
		       query(tree[v].rCh, tm + 1, tr, l, r, tog);
	}
};
