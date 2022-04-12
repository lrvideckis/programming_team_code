#pragma once

//status: stress-tested against persistent seg tree; used in various problems

struct MergeSortTree {
	struct Node {
		vector<int> vals;

		int l, r;
	};

	vector<Node> tree;

	Node combineChildren(const Node& L, const Node& R) {
		vector<int> par(L.vals.size() + R.vals.size());
		merge(L.vals.begin(), L.vals.end(), R.vals.begin(), R.vals.end(), par.begin());
		return Node{par, L.l, R.r};
	}

	//There's no constructor `SegmentTree(int size)` because how to initialize l,r in nodes without calling build?
	//the whole point of this constructor was to be simpler by not calling build
	MergeSortTree(const vector<int>& arr)  {
		int n = arr.size(), size = 1;
		while (size < n) size <<= 1;
		size <<= 1;
		tree.resize(size);
		build(arr, 1, 0, n - 1);
	}
	void build(const vector<int>& arr, int node, int start, int end) {
		if (start == end) {
			tree[node] = Node {
				vector<int>{arr[start]},
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
	int query(int l, int r, int x) {
		return query(1, l, r, x);
	}
	int query(int node, int l, int r, int x) {
		int start = tree[node].l, end = tree[node].r;
		if (r < start || end < l) return 0;
		if (l <= start && end <= r) {
			vector<int>& v = tree[node].vals;
			return lower_bound(v.begin(), v.end(), x) - v.begin();
		}
		return query(2 * node, l, r, x) + query(2 * node + 1, l, r, x);
	}
};
