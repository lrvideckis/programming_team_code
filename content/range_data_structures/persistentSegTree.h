//modified from https://cp-algorithms.com/data_structures/segment_tree.html#preserving-the-history-of-its-values-persistent-segment-tree
//tested on https://www.spoj.com/problems/PSEGTREE/
struct persistentSegTree {

	struct Node {
		int lCh, rCh;//children, indexes into `tree` -> either both -1 or both exist
		ll sum;
		int l, r; //defines range of node
	};

	vector<Node> tree;
	vector<int> roots;

	persistentSegTree(const vector<ll>& arr) {
		roots.push_back(build(arr, 0, (int)arr.size() - 1));
	}
	int build(const vector<ll>& arr, int tl, int tr) {
		if (tl == tr) {
			tree.push_back({-1, -1, arr[tl], tl, tr});
			return tree.size()-1;
		}
		int tm = (tl + tr) / 2;
		int lCh = build(arr, tl, tm);
		int rCh = build(arr, tm + 1, tr);
		ll sum = tree[lCh].sum + tree[rCh].sum;
		tree.push_back({lCh, rCh, sum, tl, tr});
		return tree.size()-1;
	}

	void update(int version, int pos, ll diff) {
		roots.push_back(updateImpl(roots[version], pos, diff));
	}
	int updateImpl(int v, int pos, ll diff) {
		if (tree[v].l == tree[v].r) {
			tree.push_back({-1, -1, tree[v].sum + diff, tree[v].l, tree[v].r});
			return tree.size()-1;
		}
		int lCh = tree[v].lCh;
		int rCh = tree[v].rCh;
		if (pos <= (tree[v].l + tree[v].r) / 2) {
			lCh = updateImpl(tree[v].lCh, pos, diff);
		} else {
			rCh = updateImpl(tree[v].rCh, pos, diff);
		}
		ll sum = tree[lCh].sum + tree[rCh].sum;
		tree.push_back({lCh, rCh, sum, tree[v].l, tree[v].r});
		return tree.size()-1;
	}

	ll query(int version, int l, int r) {
		return queryImpl(roots[version], l, r);
	}
	ll queryImpl(int v, int l, int r) {
		if (tree[v].r < l || r < tree[v].l)
			return 0;
		if (l <= tree[v].l && tree[v].r <= r)
			return tree[v].sum;
		return queryImpl(tree[v].lCh, l, r) + queryImpl(tree[v].rCh, l, r);
	}
};
