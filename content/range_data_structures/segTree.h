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

	//change to unordered_map<int, Node> for implicit seg tree. Although I've TLE'd multiple times doing this
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

	SegmentTree(const vector<ll>& arr) : n((int) arr.size()) {
		auto build = [&](auto&& buildPtr, int node, int start, int end) -> void {
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
				buildPtr(buildPtr, 2 * node, start, mid);
				buildPtr(buildPtr, 2 * node + 1, mid + 1, end);
				tree[node] = combineChildren(tree[2 * node], tree[2 * node + 1]);
			}
		};
		int size = 1;
		while (size < n) size <<= 1;
		size <<= 1;
		tree.resize(size);
		build(build, 1, 0, n - 1);
	}
	//inclusive range: [l,r]
	void update(int l, int r, ll diff) {
		auto update = [&](auto&& updatePtr, int node) -> void {
			pushLazy(node);
			int start = tree[node].l, end = tree[node].r;
			if (r < start || end < l) return;
			if (l <= start && end <= r) {
				applyDeltaOnRange(node, diff);
				return;
			}
			updatePtr(updatePtr, 2 * node);
			updatePtr(updatePtr, 2 * node + 1);
			tree[node] = combineChildren(tree[2 * node], tree[2 * node + 1]);
		};
		update(update, 1);
	}
	//inclusive range: [l,r]
	Node query(int l, int r) {
		auto query = [&](auto&& queryPtr, int node) -> Node {
			int start = tree[node].l, end = tree[node].r;
			if (r < start || end < l) return Node();   //l,r is uninitialized -> access means undefined behavior
			pushLazy(node);
			if (l <= start && end <= r) return tree[node];
			return combineChildren(
			    queryPtr(queryPtr, 2 * node),
			    queryPtr(queryPtr, 2 * node + 1)
			);
		};
		return query(query, 1);
	}
};
