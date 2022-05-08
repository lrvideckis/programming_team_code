#pragma once

//status: stress tested && AC's on https://cses.fi/problemset/task/1144
//see TODO for lines of code which usually need to change (not a complete list)

const int N = 1.5e7; //TODO

struct Node {
	long long val;//could represent max, sum, etc
	long long lazy;
	int lCh, rCh; // children, indexes into `tree`, -1 for null
} tree[N];

struct implicitLazySegTree {

	int NEW_NODE, rootL, rootR;//[rootL, rootR] defines range of root node; handles negatives

	implicitLazySegTree(int l, int r) : NEW_NODE(0), rootL(l), rootR(r) {
		assert(l <= r);
		tree[NEW_NODE++] = {0, 0, -1, -1}; //TODO
	}

	static long long combine(long long val_l, long long val_r) {
		return val_l + val_r; //TODO
	}

	void applyDeltaOnRange(int v, int tl, int tr, long long add) {
		tree[v].val += (tr - tl + 1) * add; //TODO
		if (tl != tr) {
			tree[tree[v].lCh].lazy += add; //TODO
			tree[tree[v].rCh].lazy += add;
		}
	}

	void push(int v, int tl, int tr) {
		if (tl != tr && tree[v].lCh == -1) {
			assert(NEW_NODE + 1 < N);
			tree[v].lCh = NEW_NODE;
			tree[NEW_NODE++] = {0, 0, -1, -1}; //TODO
			tree[v].rCh = NEW_NODE;
			tree[NEW_NODE++] = {0, 0, -1, -1};
		}
		if (tree[v].lazy) {
			applyDeltaOnRange(v, tl, tr, tree[v].lazy);
			tree[v].lazy = 0;
		}
	}

	//update range [l,r] with `add`
	void update(int l, int r, long long add) {
		update(0, rootL, rootR, l, r, add);
	}
	void update(int v, int tl, int tr, int l, int r, long long add) {
		push(v, tl, tr);
		if (tr < l || r < tl)
			return;
		if (l <= tl && tr <= r)
			return applyDeltaOnRange(v, tl, tr, add);
		int tm = tl + (tr - tl) / 2;
		update(tree[v].lCh, tl, tm, l, r, add);
		update(tree[v].rCh, tm + 1, tr, l, r, add);
		tree[v].val = combine(tree[tree[v].lCh].val, tree[tree[v].rCh].val);
	}

	//query range [l,r]
	long long query(int l, int r) {
		return query(0, rootL, rootR, l, r);
	}
	long long query(int v, int tl, int tr, int l, int r) {
		if (tr < l || r < tl)
			return 0; //TODO
		push(v, tl, tr);
		if (l <= tl && tr <= r)
			return tree[v].val;
		int tm = tl + (tr - tl) / 2;
		return combine(query(tree[v].lCh, tl, tm, l, r),
		               query(tree[v].rCh, tm + 1, tr, l, r));
	}
};
