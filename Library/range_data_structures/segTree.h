#pragma once

//status: tested on random inputs

const long long inf = 1e18;

struct SegmentTree {
	struct Node {
		long long sum = 0;
		long long mx = -inf;
		long long mn = inf;

		int l, r;

		int len() const {
			return r - l + 1;
		}

		long long lazy = 0;
	};

	vector<Node> tree;

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
	void applyDeltaOnRange(int node, long long delta) {
		tree[node].sum += tree[node].len() * delta;
		tree[node].mx += delta;
		tree[node].mn += delta;
		if (tree[node].len() > 1) {
			tree[2 * node].lazy += delta;
			tree[2 * node + 1].lazy += delta;
		}
	}
	//apply lazy value to range
	void pushLazy(int node) {
		long long& currLazy = tree[node].lazy;
		if (currLazy) {
			applyDeltaOnRange(node, currLazy);
			currLazy = 0;
		}
	}
	/*********************/

	//There's no constructor `SegmentTree(int size)` because how to initialize l,r in nodes without calling build?
	//the whole point of this constructor was to be simpler by not calling build
	SegmentTree(const vector<long long>& arr) {
		int n = arr.size(), size = 1;
		while (size < n) size <<= 1;
		size <<= 1;
		tree.resize(size);
		build(arr, 1, 0, n - 1);
	}
	void build(const vector<long long>& arr, int node, int start, int end) {
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

	//inclusive range: [updL,updR]
	void update(int updL, int updR, long long diff) {
		update(1, updL, updR, diff);
	}
	void update(int node, int updL, int updR, long long diff) {
		pushLazy(node);
		int ndL = tree[node].l, ndR = tree[node].r;
		if (updR < ndL || ndR < updL) return;
		if (updL <= ndL && ndR <= updR)
			return applyDeltaOnRange(node, diff);
		update(2 * node, updL, updR, diff);
		update(2 * node + 1, updL, updR, diff);
		tree[node] = combineChildren(tree[2 * node], tree[2 * node + 1]);
	}

	//inclusive range: [qryL,qryR]
	Node query(int qryL, int qryR) {
		return query(1, qryL, qryR);
	}
	Node query(int node, int qryL, int qryR) {
		int ndL = tree[node].l, ndR = tree[node].r;
		if (qryR < ndL || ndR < qryL) return Node();   //l,r is uninitialized -> access means undefined behavior
		pushLazy(node);
		if (qryL <= ndL && ndR <= qryR) return tree[node];
		return combineChildren(
		           query(2 * node, qryL, qryR),
		           query(2 * node + 1, qryL, qryR)
		       );
	}
};
