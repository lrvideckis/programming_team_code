struct Node {
	ll sum = 0;
	ll mx = 0;
	ll mn = 0;
};

struct SegmentTree {
	vector<Node> tree;
	vector<ll> lazy;
	int n,size,l,r;
	ll diff;
	const ll inf = 1e18;

	/*implement these*/
	const Node zero = {0, -inf, inf};
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
			lazy[2*node] += delta;
			lazy[2*node+1] += delta;
		}
	}

	SegmentTree(int currSize) : n(currSize) {
		size = 1;
		while(size < n) size<<=1;
		size<<=1;
		tree.resize(size);
		lazy.resize(size, 0);
	}
	SegmentTree(const vector<ll> &arr) : n((int)arr.size()) {
		size = 1;
		while(size < n) size<<=1;
		size<<=1;
		tree.resize(size);
		lazy.resize(size, 0);
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
		ll &currLazy = lazy[node];
		if(currLazy) {
			combineRange(node, start, end, currLazy);
			currLazy = 0;
		}
	}
	void update(int L, int R, ll Diff) {l=L,r=R,diff=Diff;update2(1,0,n-1);}
	Node query(int L, int R) {l=L,r=R;return query2(1, 0, n-1);}
	void update2(int node, int start, int end) {
		push(node, start, end);
		if(start > end || start > r || end < l) return;
		if(start >= l && end <= r) {
			combineRange(node, start, end, diff);
			return;
		}
		int mid = (start + end) / 2;
		update2(2*node,start,mid);
		update2(2*node+1,mid+1,end);
		tree[node] = combine(tree[2*node], tree[2*node+1]);
	}
	Node query2(int node, int start, int end) {
		if(r < start || end < l) return zero;
		push(node, start, end);
		if(l <= start && end <= r) return tree[node];
		int mid = (start+end)/2;
		return combine(query2(2*node,start,mid), query2(2*node+1,mid+1,end));
	}
};
