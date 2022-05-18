#pragma once

//status: stress-tested against persistent seg tree kth-smallest in range

struct MergeSortTree {
	struct Node {
		vector<int> vals;

		int l, r;

		//returns 1 + (# of nodes in left child's subtree)
		//https://cp-algorithms.com/data_structures/segment_tree.html#memory-efficient-implementation
		int rCh() const {
			return ((r - l) & ~1) + 2;
		}
	};

	vector<Node> tree;

	//There's no constructor `segTree(int size)` because how to initialize l,r in nodes without calling build?
	//the whole point of `segTree(int size)` was to be simpler by not calling build
	MergeSortTree(const vector<int>& arr) : tree(2 * (int) arr.size() - 1) {
		build(arr, 0, 0, (int) arr.size() - 1);
	}
	void build(const vector<int>& arr, int v, int tl, int tr) {
		if (tl == tr) {
			tree[v] = {
				{arr[tl]},
				tl,
				tr
			};
		} else {
			int tm = tl + (tr - tl) / 2;
			build(arr, v + 1, tl, tm);
			build(arr, v + 2 * (tm - tl + 1), tm + 1, tr);
			tree[v] = combine(tree[v + 1], tree[v + 2 * (tm - tl + 1)]);
		}
	}

	Node combine(const Node& L, const Node& R) {
		vector<int> par(L.vals.size() + R.vals.size());
		merge(L.vals.begin(), L.vals.end(), R.vals.begin(), R.vals.end(), par.begin());
		return {par, L.l, R.r};
	}

	//range [l,r]
	int query(int l, int r, int x) {
		return query(0, l, r, x);
	}
	int query(int v, int l, int r, int x) {
		if (tree[v].r < l || r < tree[v].l)
			return 0;
		if (l <= tree[v].l && tree[v].r <= r) {
			vector<int>& vals = tree[v].vals;
			return lower_bound(vals.begin(), vals.end(), x) - vals.begin();
		}
		return query(v + 1, l, r, x) +
		       query(v + tree[v].rCh(), l, r, x);
	}
};
