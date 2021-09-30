const ll inf = 1e18;

struct Node {
	ll sum = 0;
	ll mx = 0;
	ll mn = 0;

	ll lazy = 0;
};

struct SegmentTree {
	vector<Node> tree;
	int n;

	/*implement these*/
	const Node zero = {0, -inf, inf, 0};
	Node combine(const Node &L, const Node &R) {
		Node par;
		par.sum = L.sum + R.sum;
		par.mx = max(L.mx, R.mx);
		par.mn = min(L.mn, R.mn);
		return par;
	}
	void combineRange(int node, int start, int end, ll delta) {
		tree[node].sum += (end-start+1) * delta;
		tree[node].mx += delta;
		tree[node].mn += delta;
		if(start != end) {
			tree[2*node].lazy += delta;
			tree[2*node+1].lazy += delta;
		}
	}

	SegmentTree(int currSize) : n(currSize) {
		int size = 1;
		while(size < n) size<<=1;
		size<<=1;
		tree.resize(size);
	}
	SegmentTree(const vector<ll> &arr) : n((int)arr.size()) {
		int size = 1;
		while(size < n) size<<=1;
		size<<=1;
		tree.resize(size);
		build(arr, 1, 0, n-1);
	}
	void build(const vector<ll> &arr, int node, int start, int end) {
		if(start == end) {
			tree[node].sum = arr[start];
			tree[node].mx = arr[start];
			tree[node].mn = arr[start];
		} else {
			int mid = (start+end)/2;
			build(arr, 2*node, start, mid);
			build(arr, 2*node+1, mid+1, end);
			tree[node] = combine(tree[2*node], tree[2*node+1]);
		}
	}
	void push(int node, int start, int end) {
		ll &currLazy = tree[node].lazy;
		if(currLazy) {
			combineRange(node, start, end, currLazy);
			currLazy = 0;
		}
	}
	void update(int l, int r, ll diff) {update(1, 0, n-1, l, r, diff);}
	void update(int node, int start, int end, int l, int r, ll diff) {
		push(node, start, end);
		if(r < start || end < l) return;
		if(l <= start && end <= r) {
			combineRange(node, start, end, diff);
			return;
		}
		int mid = (start + end) / 2;
		update(2*node, start, mid, l, r, diff);
		update(2*node+1, mid+1, end, l, r, diff);
		tree[node] = combine(tree[2*node], tree[2*node+1]);
	}
	Node query(int l, int r) {return query(1, 0, n-1, l, r);}
	Node query(int node, int start, int end, int l, int r) {
		if(r < start || end < l) return zero;
		push(node, start, end);
		if(l <= start && end <= r) return tree[node];
		int mid = (start+end)/2;
		return combine(query(2*node, start, mid, l, r), query(2*node+1, mid+1, end, l, r));
	}
};
