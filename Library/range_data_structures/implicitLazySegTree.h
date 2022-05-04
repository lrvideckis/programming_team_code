#pragma once

//status: stress tested && AC's on https://cses.fi/problemset/task/1144
//see TODO for lines of code which usually need to change (not a complete list)

struct Node {
	long long val;//could represent max, sum, etc
	long long lazy;
	int lCh, rCh; // children, indexes into `tree`, -1 for null
} tree[(int)1.5e7/*360 megabytes*/]; //TODO

struct implicitLazySegTree {

	int NEW_NODE, rootL, rootR;//[rootL, rootR] defines range of root node; handles negatives

	implicitLazySegTree(int l, int r) : NEW_NODE(0), rootL(l), rootR(r) {
		assert(l <= r);
		tree[NEW_NODE++] = {0, 0, -1, -1}; //TODO
	}

	implicitLazySegTree(const vector<long long>& arr) : implicitLazySegTree(0, (int)arr.size() - 1) {
		build(arr, 0, rootL, rootR);
	}
	void build(const vector<long long>& arr, int v, int tl, int tr) {
		if (tl == tr)
			tree[v].val = arr[tl];
		else {
			push(v, tl, tr);
			int tm = tl + (tr - tl) / 2;
			build(arr, tree[v].lCh, tl, tm);
			build(arr, tree[v].rCh, tm + 1, tr);
			tree[v].val = combine(tree[tree[v].lCh].val, tree[tree[v].rCh].val);
		}
	}

	static long long combine(long long val_l, long long val_r) {
		return val_l + val_r; //TODO
	}

	void applyDeltaOnRange(int v, int tl, int tr, long long add) {
		tree[v].val += (tr - tl + 1) * add; //TODO
		if (tl != tr) {
			tree[tree[v].lCh].lazy += add;
			tree[tree[v].rCh].lazy += add;
		}
	}

	void push(int v, int tl, int tr) {
		if (tl != tr && tree[v].lCh == -1) {
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
		if (l > r)
			return;
		if (l == tl && tr == r)
			return applyDeltaOnRange(v, tl, tr, add);
		int tm = tl + (tr - tl) / 2;
		update(tree[v].lCh, tl, tm, l, min(r, tm), add);
		update(tree[v].rCh, tm + 1, tr, max(l, tm + 1), r, add);
		tree[v].val = combine(tree[tree[v].lCh].val, tree[tree[v].rCh].val);
	}

	//query range [l,r]
	//we don't allocate nodes on query using this trick https://codeforces.com/blog/entry/72626
	//ugh, I'm unhappy with how complicated this is. For a simpler; 10% slower version, see:
	//https://github.com/lrvideckis/Programming-Team-Code/blob/af398d903ab89f924fc0651f97f158ebfc3d5d27/Library/range_data_structures/implicitLazySegTree.h
	long long query(int l, int r) const {
		return query(0, rootL, rootR, l, r, 0LL);
	}
	long long query(int v, int tl, int tr, int l, int r, long long lazy) const {
		if (l > r)
			return 0; //TODO
		if (v == -1)
			return (r - l + 1) * lazy; //TODO
		lazy += tree[v].lazy;
		if (l == tl && tr == r)
			return tree[v].val + (r - l + 1) * lazy; //TODO
		int tm = tl + (tr - tl) / 2;
		return combine(query(tree[v].lCh, tl, tm, l, min(r, tm), lazy),
		               query(tree[v].rCh, tm + 1, tr, max(l, tm + 1), r, lazy));
	}
};
