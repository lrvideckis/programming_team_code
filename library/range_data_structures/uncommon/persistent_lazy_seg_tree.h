#pragma once
//status: not tested
struct persistent_lazy_seg_tree {
	struct node {
		int l_ch, r_ch;//children, indexes into `tree`
		int sum;
		bool lazy_tog;
	};
	int sz;
	deque<node> tree;
	vector<int> roots;
	//implicit
	persistent_lazy_seg_tree(int a_sz) : sz(a_sz) {
		tree.push_back({0, 0, 0, 0}); //acts as null
		roots.push_back(0);
	}
	void push(int v, int tl, int tr) {
		if (tl != tr) {
			tree.push_back(tree[tree[v].l_ch]);
			tree[v].l_ch = tree.size() - 1;
			tree.push_back(tree[tree[v].r_ch]);
			tree[v].r_ch = tree.size() - 1;
		}
		if (tree[v].lazy_tog) {
			tree[v].sum = (tr - tl + 1) - tree[v].sum;
			tree[v].lazy_tog = false;
			if (tl != tr) {
				tree[tree[v].l_ch].lazy_tog ^= 1;
				tree[tree[v].r_ch].lazy_tog ^= 1;
			}
		}
	}
	void set(int idx, int new_val) {
		tree.push_back(tree[roots.back()]);//allocate top down
		roots.push_back(tree.size() - 1);
		set(roots.back(), 0, sz - 1, idx, new_val);
	}
	void set(int v, int tl, int tr, int idx, int new_val) {
		push(v, tl, tr);
		if (tr < idx || idx < tl)
			return;
		if (idx <= tl && tr <= idx) {
			tree[v].sum = new_val;
			return;
		}
		int tm = (tl + tr) / 2;
		int l_ch = tree[v].l_ch;
		int r_ch = tree[v].r_ch;
		set(l_ch, tl, tm, idx, new_val);
		set(r_ch, tm + 1, tr, idx, new_val);
		tree[v].sum = tree[l_ch].sum + tree[r_ch].sum;
	}
	void toggle_range(int l, int r) {
		tree.push_back(tree[roots.back()]);//allocate top down
		roots.push_back(tree.size() - 1);
		toggle_range(roots.back(), 0, sz - 1, l, r);
	}
	void toggle_range(int v, int tl, int tr, int l, int r) {
		push(v, tl, tr);
		if (tr < l || r < tl)
			return;
		int l_ch = tree[v].l_ch;
		int r_ch = tree[v].r_ch;
		if (l <= tl && tr <= r) {
			tree[v].sum = (tr - tl + 1) - tree[v].sum;
			if (tl != tr) {
				tree[l_ch].lazy_tog ^= 1;
				tree[r_ch].lazy_tog ^= 1;
			}
			return;
		}
		int tm = (tl + tr) / 2;
		toggle_range(l_ch, tl, tm, l, r);
		toggle_range(r_ch, tm + 1, tr, l, r);
		tree[v].sum = tree[l_ch].sum + tree[r_ch].sum;
	}
	//let's use implementation trick described here https://codeforces.com/blog/entry/72626
	//so that we don't have to propagate lazy vals and thus we don't have to allocate new nodes
	int query(int l, int r) const {
		int version = roots.size() - 1;
		int root = roots[version];
		return query(root, 0, sz - 1, l, r, tree[root].lazy_tog);
	}
	int query(int v, int tl, int tr, int l, int r, bool tog) const {
		if (v == 0 || tr < l || r < tl)
			return 0;
		if (l <= tl && tr <= r) {
			int sum = tree[v].sum;
			if (tree[v].lazy_tog) sum = (tr - tl + 1) - sum;
			return sum;
		}
		int tm = (tl + tr) / 2;
		tog ^= tree[v].lazy_tog;
		return query(tree[v].l_ch, tl, tm, l, r, tog) +
		       query(tree[v].r_ch, tm + 1, tr, l, r, tog);
	}
};
