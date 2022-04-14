#pragma once

//status: stress tested && tested on https://codeforces.com/contest/52/problem/C

struct Node {
	//TODO: reorder variables to get best performance
	int lCh, rCh; // children, indexes into `tree`, -1 for null

	int l, r; // range of node: [l,r]

	ll val;//could represent max, sum, etc
	ll lazy;

	int len() const {
		return r - l + 1;
	}

} tree[(int)4e4/*TODO: update*/];

struct implicitLazySegTree {

	int NEW_NODE;

	implicitLazySegTree(int sz) : NEW_NODE(0) {
		tree[NEW_NODE++] = {-1, -1, 0, sz - 1, 0, 0}; //root node
	}

	implicitLazySegTree(const vector<ll>& arr) : NEW_NODE(0) {
		tree[NEW_NODE++] = {-1, -1, 0, (int)arr.size() - 1, 0, 0}; //root node
		build(arr, 0);
	}
	void build(const vector<ll>& arr, int v) {
		if (tree[v].len() == 1) {
			tree[v].val = arr[tree[v].l];
		} else {
			push(v);
			build(arr, tree[v].lCh);
			build(arr, tree[v].rCh);
			tree[v].val = combine(tree[tree[v].lCh].val, tree[tree[v].rCh].val);
		}
	}

	ll combine(ll l, ll r) {
		return max(l, r); //TODO: update
	}

	void applyDeltaOnRange(int v, ll add) {
		tree[v].val += add; //TODO: update
		if (tree[v].len() > 1) {
			tree[tree[v].lCh].lazy += add;
			tree[tree[v].rCh].lazy += add;
		}
	}

	void push(int v) {
		if (tree[v].len() > 1 && tree[v].lCh == -1) {
			int tl = tree[v].l;
			int tr = tree[v].r;
			int tm = (tl + tr) / 2;
			tree[v].lCh = NEW_NODE;
			tree[NEW_NODE++] = {-1, -1, tl, tm, 0, 0};
			tree[v].rCh = NEW_NODE;
			tree[NEW_NODE++] = {-1, -1, tm+1, tr, 0, 0};
		}
		if (tree[v].lazy) {
			applyDeltaOnRange(v, tree[v].lazy);
			tree[v].lazy = 0;
		}
	}

	//add `add` to each value in range [l,r]
	void update(int l, int r, ll add) {
		update(0, l, r, add);
	}
	void update(int v, int l, int r, ll add) {
		push(v);
		if (tree[v].r < l || r < tree[v].l)
			return;
		if (l <= tree[v].l && tree[v].r <= r)
			return applyDeltaOnRange(v, add);
		update(tree[v].lCh, l, r, add);
		update(tree[v].rCh, l, r, add);
		tree[v].val = combine(tree[tree[v].lCh].val, tree[tree[v].rCh].val);
	}

	//min on range [l,r]
	ll query(int l, int r) {
		return query(0, l, r);
	}
	ll query(int v, int l, int r) {
		if (tree[v].r < l || r < tree[v].l)
			return -1e18; //TODO: update
		push(v);
		if (l <= tree[v].l && tree[v].r <= r)
			return tree[v].val;
		return combine(query(tree[v].lCh, l, r),
					   query(tree[v].rCh, l, r));
	}
};
