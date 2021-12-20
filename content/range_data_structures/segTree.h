#pragma once

const ll inf = 1e18;

struct SegmentTree {
	struct Node {
		ll sum = 0;
		ll mx = -inf;
		ll mn = inf;

		ll lazy = 0;
	};

	//change to unordered_map<int, Node> for implicit seg tree
	vector<Node> tree;
	int n;

	/***implement these***/
	Node combineChildren(const Node &L, const Node &R) {
		return Node {
			L.sum + R.sum,
			max(L.mx, R.mx),
			min(L.mn, R.mn)
		};
	}
	//what happens when delta is applied to every index in range [start,end]?
	void applyDeltaOnRange(int node, int start, int end, ll delta) {
		tree[node].sum += (end-start+1) * delta;
		tree[node].mx += delta;
		tree[node].mn += delta;
		if(start != end) {
			tree[2*node].lazy += delta;
			tree[2*node+1].lazy += delta;
		}
	}
	//apply lazy value to range
	void pushLazy(int node, int start, int end) {
		ll &currLazy = tree[node].lazy;
		if(currLazy) {
			applyDeltaOnRange(node, start, end, currLazy);
			currLazy = 0;
		}
	}
	/*********************/

	SegmentTree(int currSize) : n(currSize) {
		int size = 1;
		while(size < n) size<<=1;
		size<<=1;
		tree.resize(size, Node{0,0,0});
	}
	SegmentTree(const vector<ll> &arr) : n((int)arr.size()) {
		auto build = [&](auto&& buildPtr, int node, int start, int end) -> void {
			if(start == end) {
				tree[node] = Node {
					arr[start],
					arr[start],
					arr[start]
				};
			} else {
				int mid = (start+end)/2;
				buildPtr(buildPtr, 2*node, start, mid);
				buildPtr(buildPtr, 2*node+1, mid+1, end);
				tree[node] = combineChildren(tree[2*node], tree[2*node+1]);
			}
		};
		int size = 1;
		while(size < n) size<<=1;
		size<<=1;
		tree.resize(size);
		build(build, 1, 0, n-1);
	}
	void update(int l, int r, ll diff) {
		auto update = [&](auto&& update, int node, int start, int end, int l, int r, ll diff) -> void {
			pushLazy(node, start, end);
			if(r < start || end < l) return;
			if(l <= start && end <= r) {
				applyDeltaOnRange(node, start, end, diff);
				return;
			}
			int mid = (start + end) / 2;
			update(update, 2*node, start, mid, l, r, diff);
			update(update, 2*node+1, mid+1, end, l, r, diff);
			tree[node] = combineChildren(tree[2*node], tree[2*node+1]);
		};
		update(update, 1, 0, n-1, l, r, diff);
	}
	Node query(int l, int r) {
		auto query = [&](auto&& query, int node, int start, int end, int l, int r) -> Node {
			if(r < start || end < l) return Node();
			pushLazy(node, start, end);
			if(l <= start && end <= r) return tree[node];
			int mid = (start+end)/2;
			return combineChildren(query(query, 2*node, start, mid, l, r), query(query, 2*node+1, mid+1, end, l, r));
		};
		return query(query, 1, 0, n-1, l, r);
	}
};
