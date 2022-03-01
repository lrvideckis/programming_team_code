#pragma once

//status: tested on random inputs

const ll inf = 1e18;

struct SegmentTree {
	struct Node {
		ll sum = 0;
		ll mx = -inf;
		ll mn = inf;

		int l, r;

		ll lazy = 0;
	};

	//For implicit seg tree (Although I've TLE'd multiple times doing this):
	//    1) change `tree` to unordered_map<int, Node>
	//    2) update l,r when allocating new Nodes when going down tree
	vector<Node> tree;
	int n;

	/***implement these***/
	Node combineChildren(const Node& L, const Node& R) {
		return Node {
			L.sum + R.sum,
			max(L.mx, R.mx),
			min(L.mn, R.mn),
			L.l,
			R.r
			//Note lazy value initializes to 0 here which is ok since we always push lazy down&reset before combining back up
		};
	}
	//what happens when delta is applied to every index in range [start,end]?
	void applyDeltaOnRange(int node, ll delta) {
		int start = tree[node].l, end = tree[node].r;
		tree[node].sum += (end - start + 1) * delta;
		tree[node].mx += delta;
		tree[node].mn += delta;
		if (start != end) {
			tree[2 * node].lazy += delta;
			tree[2 * node + 1].lazy += delta;
		}
	}
	//apply lazy value to range
	void pushLazy(int node) {
		ll& currLazy = tree[node].lazy;
		if (currLazy) {
			applyDeltaOnRange(node, currLazy);
			currLazy = 0;
		}
	}
	/*********************/

	//There's no constructor `SegmentTree(int size)` because how to initialize l,r in nodes without calling build?
	SegmentTree(const vector<ll>& arr) : n((int) arr.size()) {
		int size = 1;
		while (size < n) size <<= 1;
		size <<= 1;
		tree.resize(size);
		build(arr, 1, 0, n - 1);
	}
	void build(const vector<ll>& arr, int node, int start, int end) {
		if (start == end) {
			tree[node] = Node {
				arr[start],
				arr[start],
				arr[start],
				start,
				end
			};
		} else {
			int mid = (start + end) / 2;
			build(arr, 2 * node, start, mid);
			build(arr, 2 * node + 1, mid + 1, end);
			tree[node] = combineChildren(tree[2 * node], tree[2 * node + 1]);
		}
	}

	//inclusive range: [l,r]
	void update(int l, int r, ll diff) {
		update(1, l, r, diff);
	}
	void update(int node, int l, int r, ll diff) {
		pushLazy(node);
		int start = tree[node].l, end = tree[node].r;
		if (r < start || end < l) return;
		if (l <= start && end <= r) {
			applyDeltaOnRange(node, diff);
			return;
		}
		update(2 * node, l, r, diff);
		update(2 * node + 1, l, r, diff);
		tree[node] = combineChildren(tree[2 * node], tree[2 * node + 1]);
	};

	//inclusive range: [l,r]
	Node query(int l, int r) {
		return query(1, l, r);
	}
	Node query(int node, int l, int r) {
		int start = tree[node].l, end = tree[node].r;
		if (r < start || end < l) return Node();   //l,r is uninitialized -> access means undefined behavior
		pushLazy(node);
		if (l <= start && end <= r) return tree[node];
		return combineChildren(
		           query(2 * node, l, r),
		           query(2 * node + 1, l, r)
		       );
	};
};
