/**
 * @see https://cp-algorithms.com/data_structures/segment_tree.html# preserving-the-history-of-its-values-persistent-segment-tree
 */
struct PST {
	struct node {
		int64_t sum;
		int lch, rch;
		node(int64_t a_sum, int a_lch, int a_rch) : sum(a_sum), lch(a_lch), rch(a_rch) {}
	};
	int root_l, root_r;
	vector<int> roots; /**< tree[roots[i]] = root node at version i */
	deque<node> tree;
	/**
	 * @param a_root_l,a_root_r defines range [root_l, root_l) of root node, can be
	 * negative
	 * @time O(1)
	 * @space O(1)
	 */
	PST(int a_root_l, int a_root_r) :
		root_l(a_root_l), root_r(a_root_r), roots(1), tree(1, {0LL, 0, 0}) {}
	/**
	 * @param idx,change does a[idx] += change
	 * @param version which version to update. Each call to update creates a
	 * new version. Initially there is a dummy version.
	 * @time O(log(root_r - root_l))
	 * @space O(log(root_r - root_l)) new nodes are pushed back onto `tree`; (and for recursion stack)
	 */
	void update(int idx, int64_t change, int version) {
		assert(root_l <= idx && idx < root_r);
		assert(0 <= version && version < ssize(roots));
		roots.push_back(update_impl(idx, change, root_l, root_r, roots[version]));
	}
	int update_impl(int idx, int64_t change, int tl, int tr, int u) {
		if (tr - tl == 1) {
			tree.emplace_back(tree[u].sum + change, 0, 0);
			return ssize(tree) - 1;
		}
		int tm = tl + (tr - tl) / 2;
		int lch = tree[u].lch;
		int rch = tree[u].rch;
		if (idx < tm)
			lch = update_impl(idx, change, tl, tm, lch);
		else
			rch = update_impl(idx, change, tm, tr, rch);
		tree.emplace_back(tree[lch].sum + tree[rch].sum, lch, rch);
		return ssize(tree) - 1;
	}
	/**
	 * @param le, ri defines range [le, ri)
	 * @param version which version to query
	 * @returns a[le] + a[le + 1] + ... + a[ri - 1] during the `version`-th version
	 * @time O(log(root_r - root_l))
	 * @space O(log(root_r - root_l)) for recursion stack, no new nodes are allocated
	 */
	inline int64_t query(int le, int ri, int version) {
		assert(root_l <= le && ri <= root_r);
		assert(0 <= version && version < ssize(roots));
		return query_impl(le, ri, root_l, root_r, roots[version]);
	}
	int64_t query_impl(int le, int ri, int tl, int tr, int u) {
		if (u == 0 || ri <= tl || tr <= le) return 0;
		if (le <= tl && tr <= ri) return tree[u].sum;
		int tm = tl + (tr - tl) / 2;
		return query_impl(le, ri, tl, tm, tree[u].lch) +
		       query_impl(le, ri, tm, tr, tree[u].rch);
	}
};
/**
 * @see https://cp-algorithms.com/data_structures/segment_tree.html# preserving-the-history-of-its-values-persistent-segment-tree
 */
struct kth_smallest {
	PST pst;
	/**
	 * @param a,minv,maxv must satisfy: minv <= a[i] < maxv
	 * @time O(n log(maxv - minv))
	 * @space O(n log(maxv - minv)) nodes are pushed back onto PST::tree
	 */
	kth_smallest(const vector<int>& a, int minv, int maxv) : pst(minv, maxv) {
		for (int i = 0; i < ssize(a); i++)
			pst.update(a[i], 1, i);
	}
	/**
	 * @param le,ri defines range [le, ri)
	 * @param k must satisfy 1 <= k <= ri - le
	 * @returns kth smallest number in range.
	 *     - query(le,ri,1) returns the min
	 *     - query(le,ri,(ri-le)) returns the max
	 * @time O(log(maxv - minv))
	 * @space O(log(maxv - minv)) for recursion stack; no new nodes are allocated
	 */
	inline int query(int le, int ri, int k) {
		assert(0 <= le && ri < ssize(pst.roots));
		assert(1 <= k && k <= ri - le);
		return query_impl(k, pst.root_l, pst.root_r, pst.roots[le], pst.roots[ri]);
	}
	int query_impl(int k, int tl, int tr, int vl, int vr) {
		if (tr - tl == 1) return tl;
		int tm = tl + (tr - tl) / 2;
		int left_count = pst.tree[pst.tree[vr].lch].sum - pst.tree[pst.tree[vl].lch].sum;
		if (left_count >= k) return query_impl(k, tl, tm, pst.tree[vl].lch, pst.tree[vr].lch);
		return query_impl(k - left_count, tm, tr, pst.tree[vl].rch, pst.tree[vr].rch);
	}
};
