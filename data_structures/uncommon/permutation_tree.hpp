/**
 * @code{.cpp}
       vector<int64_t> a;
       auto ri = mono_st(a, less()); // greater(), less_equal(), greater_equal()
       for (int i = n - 1; i >= 0; i--)
           for (int j = i + 1; j != ri[i]; j = ri[j])
               // for all k in [j, ri[j]): cmp(a[i], a[k])
               // these ranges are disjoint, and union to [i + 1, ri[i])
 * @endcode
 * @param a array
 * @param cmp any transitive compare operator
 * @returns array ri where ri[i] = max integer such that:
 *     for all k in [i + 1, ri[i]): cmp(a[i], a[k])
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
template <class T, class F> vector<int> mono_st(const vector<T>& a, F cmp) {
	vector<int> ri(ssize(a));
	for (int i = ssize(a) - 1; i >= 0; i--)
		for (ri[i] = i + 1; ri[i] < ssize(a) && cmp(a[i], a[ri[i]]);) ri[i] = ri[ri[i]];
	return ri;
}
/**
 * @code{.cpp}
       vector<int64_t> a;
       auto ri = mono_st(a, less()), le = mono_range(ri); // greater(), less_equal(), greater_equal()
 * @endcode
 * @param ri monotonic stack array of a
 * @returns (if you use less()) vector le such that:
 *     - le[i] < i < ri[i]
 *     - a[i] is the min of exclusive-exclusive range (le[i], ri[i])
 *     - le[i] is the max index such that a[le[i]] < a[i], or -1
 *     - ri[i] is the min index such that a[i] >= a[ri[i]], or n
 * @time O(n)
 * @space two O(n) vectors are allocated and returned
 */
vector<int> mono_range(const vector<int>& ri) {
	vector le(ssize(ri), -1);
	for (int i = 0; i < ssize(ri); i++)
		for (int j = i + 1; j != ri[i]; j = ri[j]) le[j] = i;
	return le;
}
/**
 *   when cmp is less():
 *   a = {2, 1, 3, 1, 1, 0, 2, 2, 1, 0, 2}
 *       (---------------------------x---)
 *       (---------------x---------)   (x)
 *       (------------x) | (------x)    |
 *       (---------x)    | (---x) |     |
 *       (---x---)       | (x) |  |     |
 *       (x) | (x)       |  |  |  |     |
 *        |  |  |        |  |  |  |     |
 * index: 0  1  2  3  4  5  6  7  8  9  10
 *
 * @code{.cpp}
       auto ri = mono_st(a, less()), p = cart_binary_tree(ri); // right-most min is root
       auto ri = mono_st(a, less_equal()), p = cart_binary_tree(ri); // left-most min is root
       auto ri = mono_st(a, greater()), p = cart_binary_tree(ri); // right-most max is root
       auto ri = mono_st(a, greater_equal()), p = cart_binary_tree(ri); // left-most max is root
 * @endcode
 * @param ri monotonic stack of array `a`
 * @returns parent array
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
vector<int> cart_binary_tree(const vector<int>& ri) {
	vector<int> p(ri);
	for (int i = 0; i < ssize(p); i++)
		for (int j = i + 1; j != ri[i]; j = ri[j])
			if (ri[j] == ri[i]) p[j] = i;
	return p;
}
inline int bit_floor(unsigned x) {return x ? 1 << __lg(x) : 0;}
/**
 * @see On Finding Lowest Common Ancestors: Simplification and Parallelization
 * by Baruch Schieber, Uzi Vishkin, April 1987
 */
template <class T, class F> struct linear_rmq {
	int n;
	F cmp;
	vector<T> a;
	vector<int> par_head;
	vector<unsigned> in_label, ascendant;
	/**
	 * @code{.cpp}
	       vector<int64_t> a(n);
	       linear_rmq rmq(a, less()); // right-most min
	       linear_rmq rmq(a, less_equal()); // left-most min
	       linear_rmq rmq(a, greater()); // right-most max
	       linear_rmq rmq(a, greater_equal()); // left-most max
	 * @endcode
	 * @param a_a,a_cmp array and a compare operator
	 * @time O(n)
	 * @space O(n)
	 */
	linear_rmq(const vector<T>& a_a, F a_cmp) : n(ssize(a_a)), cmp(a_cmp), a(a_a), par_head(n + 1), in_label(n), ascendant(n) {
		vector<int> ri(mono_st(a, cmp)), le(mono_range(ri)), p(cart_binary_tree(ri));
		for (int i = 0; i < n; i++)
			in_label[i] = ri[i] & -bit_floor(unsigned((le[i] + 1) ^ ri[i]));
		for (int i = 0; i < n; i++)
			if (p[i] == n || in_label[p[i]] != in_label[i]) {
				par_head[in_label[i]] = p[i];
				int to_add = in_label[i] & -in_label[i];
				ascendant[le[i] + 1] += to_add;
				if (ri[i] < n) ascendant[ri[i]] -= to_add;
			}
		partial_sum(begin(ascendant), end(ascendant), begin(ascendant));
	}
	inline int lift(int u, unsigned j) {
		auto k = bit_floor(ascendant[u] ^ j);
		return k == 0 ? u : par_head[(in_label[u] & -k) | k];
	}
	/**
	 * @param le,ri defines range [min(le, ri), max(le, ri)]
	 * @returns index of min/max of range
	 * @time O(1)
	 * @space O(1)
	 */
	inline int query_idx(int le, int ri) {
		auto [x, y] = minmax(in_label[le], in_label[ri]);
		auto j = ascendant[le] & ascendant[ri] & -bit_floor((x - 1) ^ y);
		return cmp(a[le = lift(le, j)], a[ri = lift(ri, j)]) ? le : ri;
	}
};
/**
 * @see https://codeforces.com/blog/entry/78898
 * @code{.cpp}
       auto [is_join, mn_idx, mn_val, len, root, adj] = perm_tree(a);
 * @endcode
 */
struct perm_tree {
	vector<bool> is_join;
	/**
	 * [mn_idx[u], mn_idx[u] + len[u]) is range of indexes
	 * [mn_val[u], mn_val[u] + len[u]) is range of values
	 * @{
	 */
	vector<int> mn_idx, mn_val, len;
	/** @} */
	int root;
	vector<vector<int>> adj; /**< [0, n) are leaves, [n, ssize(adj)) are internal nodes */
	bool touches(int u, int v) {
		return mn_val[u] == mn_val[v] + len[v] || mn_val[v] == mn_val[u] + len[u];
	}
	int allocate(bool join, int mn_i, int mn_v, int ln, const vector<int>& ch) {
		is_join.push_back(join);
		mn_idx.push_back(mn_i);
		mn_val.push_back(mn_v);
		len.push_back(ln);
		adj.push_back(ch);
		return ssize(adj) - 1;
	}
	/**
	 * @param a permutation
	 * @time O(n)
	 * @space O(n)
	 */
	perm_tree(const vector<int>& a) {
		int n = ssize(a);
		vector<int> mn_i(n), mx_i(n);
		{
			vector<int> a_inv(n, -1);
			for (int i = 0; i < n; i++) {
				assert(0 <= a[i] && a[i] < n && a_inv[a[i]] == -1);
				a_inv[a[i]] = i;
			}
			linear_rmq rmq_min(a_inv, less());
			linear_rmq rmq_max(a_inv, greater());
			for (int i = 1; i < n; i++) {
				mn_i[i] = a_inv[rmq_min.query_idx(a[i - 1], a[i])];
				mx_i[i] = a_inv[rmq_max.query_idx(a[i - 1], a[i])];
			}
		}
		for (int i = 0; i < n; i++) allocate(0, i, a[i], 1, {});
		vector<array<int, 4>> st;
		for (int i = 0; i < n; i++) {
			int u = i;
			while (!empty(st)) {
				int v = st.back()[0];
				if (!empty(adj[v]) && touches(adj[v].back(), u)) {
					mn_val[v] = min(mn_val[v], mn_val[u]);
					len[v] += len[u];
					adj[v].push_back(u);
					u = v;
					st.pop_back();
					continue;
				}
				if (touches(u, v)) {
					u = allocate(1, mn_idx[v], min(mn_val[u], mn_val[v]), len[u] + len[v], {v, u});
					st.pop_back();
					continue;
				}
				int le = min(mn_idx[v], mn_i[mn_idx[u]]), ri = max(i, mx_i[mn_idx[u]]), idx = ssize(st) - 1;
				while (ri == i && le != mn_idx[st[idx][0]])
					le = min(le, st[idx][1]), ri = max(ri, st[idx][2]), idx = st[idx][3];
				if (ri > i) {
					st.push_back({u, le, ri, idx});
					break;
				}
				int min_val = mn_val[u];
				vector<int> ch(1 + ssize(st) - idx, u);
				for (int j = idx; j < ssize(st); j++)
					min_val = min(min_val, mn_val[ch[j - idx] = st[j][0]]);
				u = allocate(0, le, min_val, i - le + 1, ch);
				st.resize(idx);
			}
			if (empty(st)) st.push_back({u, -1, -1, -1});
		}
		assert(ssize(st) == 1);
		root = st[0][0];
	}
};
