/**
 * @code{.cpp}
       vector<long long> a;
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
       vector<long long> a;
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
	       vector<long long> a(n);
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
