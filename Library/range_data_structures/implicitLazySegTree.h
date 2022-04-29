#pragma once

//status: stress tested && tested on https://codeforces.com/contest/52/problem/C
//see TODO for all places you'll likely have to update

struct Node {
	long long val;//could represent max, sum, etc
	long long lazy;
	int lCh, rCh; // children, indexes into `tree`, -1 for null
} tree[(int)1.5e7/*360 megabytes*/]; //TODO

struct implicitLazySegTree {

	int NEW_NODE, rangeL, rangeR;//[rangeL, rangeR] defines range of root node; handles negatives

	implicitLazySegTree(int l, int r) : NEW_NODE(0), rangeL(l), rangeR(r) {
		assert(l <= r);
		tree[NEW_NODE++] = {0, 0, -1, -1}; //TODO
	}

	implicitLazySegTree(const vector<long long>& arr) : implicitLazySegTree(0, (int)arr.size() - 1) {
		build(arr, 0, rangeL, rangeR);
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

	long long combine(long long val_l, long long val_r) {
		return max(val_l, val_r); //TODO
	}

	void applyDeltaOnRange(int v, int tl, int tr, long long add) {
		tree[v].val += add; //TODO
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
		update(0, rangeL, rangeR, l, r, add);
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

	//range [l,r]
	long long query(int l, int r) {
		return query(0, rangeL, rangeR, l, r);
	}
	long long query(int v, int tl, int tr, int l, int r) {
		if (tr < l || r < tl)
			return -1e18; //TODO
		push(v, tl, tr);
		if (l <= tl && tr <= r)
			return tree[v].val;
		int tm = tl + (tr - tl) / 2;
		return combine(query(tree[v].lCh, tl, tm, l, r),
		               query(tree[v].rCh, tm + 1, tr, l, r));
	}
};
