#pragma once

//status: tested on random inputs

const long long inf = 1e18;

struct segTree {
	struct Node {
		long long sum = 0;
		long long mx = -inf;
		long long mn = inf;

		int l, r;

		int len() const {
			return r - l + 1;
		}

		//1 + (# of nodes in left child's subtree)
		//https://cp-algorithms.com/data_structures/segment_tree.html#memory-efficient-implementation
		int rCh() const {
			return ((r - l) & ~1) + 2;
		}

		long long lazy = 0;
	};

	vector<Node> tree;

	//There's no constructor `segTree(int size)` because how to initialize l,r in nodes without calling build?
	//the whole point of `segTree(int size)` was to be simpler by not calling build
	segTree(const vector<long long>& arr) : tree(2 * (int) arr.size() - 1) {
		build(arr, 0, 0, (int) arr.size() - 1);
	}
	void build(const vector<long long>& arr, int v, int tl, int tr) {
		if (tl == tr) {
			tree[v] = Node {
				arr[tl],
				arr[tl],
				arr[tl],
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
		return Node {
			L.sum + R.sum,
			max(L.mx, R.mx),
			min(L.mn, R.mn),
			L.l,
			R.r
			//Note lazy value initializes to 0 here which is ok since we always push lazy down&reset before combining back up
		};
	}

	//what happens when `add` is applied to every index in range [tree[v].l, tree[v].r]?
	void applyDeltaOnRange(int v, long long add) {
		tree[v].sum += tree[v].len() * add;
		tree[v].mx += add;
		tree[v].mn += add;
		if (tree[v].len() > 1) {
			tree[v + 1].lazy += add;
			tree[v + tree[v].rCh()].lazy += add;
		}
	}

	void push(int v) {
		if (tree[v].lazy) {
			applyDeltaOnRange(v, tree[v].lazy);
			tree[v].lazy = 0;
		}
	}

	//update range [l,r] with `add`
	void update(int l, int r, long long add) {
		update(0, l, r, add);
	}
	void update(int v, int l, int r, long long add) {
		push(v);
		if (tree[v].r < l || r < tree[v].l)
			return;
		if (l <= tree[v].l && tree[v].r <= r)
			return applyDeltaOnRange(v, add);
		update(v + 1, l, r, add);
		update(v + tree[v].rCh(), l, r, add);
		tree[v] = combine(tree[v + 1], tree[v + tree[v].rCh()]);
	}

	//range [l,r]
	Node query(int l, int r) {
		return query(0, l, r);
	}
	Node query(int v, int l, int r) {
		if (tree[v].r < l || r < tree[v].l)
			return Node(); //l,r is uninitialized -> access means undefined behavior
		push(v);
		if (l <= tree[v].l && tree[v].r <= r)
			return tree[v];
		return combine(query(v + 1, l, r),
		               query(v + tree[v].rCh(), l, r));
	}
};
