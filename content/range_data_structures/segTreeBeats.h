#pragma once

struct SegTreeBeats {
	struct Node {
		int sum;
		int mx;
		int secondMx;
		int cntMx;
	};
	vector<Node> tree;
	vector<int> lazy;
	int n, size;
	const int inf = 1e18;

	/*implement these*/
	const Node zero = {0, -inf, -inf, 0};
	Node combine(const Node &L, const Node &R) {
		Node par;
		par.sum = L.sum + R.sum;
		if(L.mx == R.mx) {
			par.cntMx = L.cntMx + R.cntMx;
		} else if(L.mx > R.mx) {
			par.cntMx = L.cntMx;
		} else {
			par.cntMx = R.cntMx;
		}
		par.mx = max(L.mx, R.mx);
		par.secondMx = -inf;
		for(int val : {L.mx, R.mx, L.secondMx, R.secondMx}) {
			if(par.mx != val) {
				assert(par.mx > val);
				par.secondMx = max(par.secondMx, val);
			}
		}
		return par;
	}
	void push(int node, int start, int end) {
		if(start == end) return;
		assert(start < end);
		for(int child : {2*node, 2*node+1}) {
			if(tree[child].mx <= tree[node].mx) continue;
			tree[child].sum -= (tree[child].mx - tree[node].mx) * tree[child].cntMx;
			tree[child].mx = tree[node].mx;
		}
	}

	SegTreeBeats(const vector<int> &arr) : n((int)arr.size()) {
		size = 1;
		while(size < n) size<<=1;
		size<<=1;
		tree.resize(size);
		lazy.resize(size, 0);
		build(arr, 1, 0, n-1);
	}
	void build(const vector<int> &arr, int node, int start, int end) {
		if(start == end) {
			tree[node].sum = arr[start];
			tree[node].mx = arr[start];
			tree[node].secondMx = -inf;
			tree[node].cntMx = 1;
		} else {
			const int mid = (start+end)/2;
			build(arr, 2*node, start, mid);
			build(arr, 2*node+1, mid+1, end);
			tree[node] = combine(tree[2*node], tree[2*node+1]);
		}
	}
	//set a[i] = min(a[i], newMn), for i in range: [l,r]
	void update(int l, int r, int newMn) {update(1, 0, n-1, l, r, newMn);}
	void update(int node, int start, int end, int l, int r, int newMn) {
		assert(start <= end);
		push(node, start, end);
		if(start > r || end < l || tree[node].mx <= newMn) return;
		if(start >= l && end <= r && tree[node].secondMx < newMn) {
			tree[node].sum -= (tree[node].mx - newMn) * tree[node].cntMx;
			tree[node].mx = newMn;
			return;
		}
		assert(start < end);
		const int mid = (start + end) / 2;
		update(2*node, start, mid, l, r, newMn);
		update(2*node+1, mid+1, end, l, r, newMn);
		tree[node] = combine(tree[2*node], tree[2*node+1]);
	}
	//query for sum/max in range [l,r]
	Node query(int l, int r) {return query(1, 0, n-1, l, r);}
	Node query(int node, int start, int end, int l, int r) {
		if(r < start || end < l) return zero;
		push(node, start, end);
		if(l <= start && end <= r) return tree[node];
		const int mid = (start+end)/2;
		return combine(query(2*node, start, mid, l, r), query(2*node+1, mid+1, end, l, r));
	}
};
