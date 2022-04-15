#pragma once

//status: stress tested && tested on https://codeforces.com/contest/52/problem/C

struct Node {
	ll val;//could represent max, sum, etc
	ll lazy;
	int lCh, rCh; // children, indexes into `tree`, -1 for null
} tree[(int)2e7/*TODO: update*/];

struct implicitLazySegTree {

	int NEW_NODE, sz;

	implicitLazySegTree(int _sz) : NEW_NODE(0), sz(_sz) {
		tree[NEW_NODE++] = {0, 0, -1, -1};
	}

	implicitLazySegTree(const vector<ll>& arr) : NEW_NODE(0), sz(arr.size()) {
		tree[NEW_NODE++] = {0, 0, -1, -1};
		build(arr, 0, 0, sz - 1);
	}
	void build(const vector<ll>& arr, int v, int tl, int tr) {
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

	ll combine(ll val_l, ll val_r) {
		return max(val_l, val_r); //TODO: update
	}

	void applyDeltaOnRange(int v, int tl, int tr, ll add) {
		tree[v].val += add; //TODO: update
		if (tl != tr) {
			tree[tree[v].lCh].lazy += add;
			tree[tree[v].rCh].lazy += add;
		}
	}

	void push(int v, int tl, int tr) {
		if (tl != tr && tree[v].lCh == -1) {
			tree[v].lCh = NEW_NODE;
			tree[NEW_NODE++] = {0, 0, -1, -1};
			tree[v].rCh = NEW_NODE;
			tree[NEW_NODE++] = {0, 0, -1, -1};
		}
		if (tree[v].lazy) {
			applyDeltaOnRange(v, tl, tr, tree[v].lazy);
			tree[v].lazy = 0;
		}
	}

	//add `add` to each value in range [l,r]
	void update(int l, int r, ll add) {
		update(0, 0, sz - 1, l, r, add);
	}
	void update(int v, int tl, int tr, int l, int r, ll add) {
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

	//max on range [l,r]
	ll query(int l, int r) {
		return query(0, 0, sz - 1, l, r);
	}
	ll query(int v, int tl, int tr, int l, int r) {
		if (tr < l || r < tl)
			return -1e18; //TODO: update
		push(v, tl, tr);
		if (l <= tl && tr <= r)
			return tree[v].val;
		int tm = tl + (tr - tl) / 2;
		return combine(query(tree[v].lCh, tl, tm, l, r),
		               query(tree[v].rCh, tm + 1, tr, l, r));
	}
};
