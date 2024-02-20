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
 *   when cmp is less_equal():
 *   a = {2, 1, 3, 1, 1, 0, 2, 2, 1, 0, 2}
 *       (---------------x---------------)
 *       (---x---------) | (------x)   (x)
 *       (x) | (x)       | (x---) |     |
 *        |  |  |        |  |     |     |
 * index: 0  1  2  3  4  5  6  7  8  9  10
 *
 * nodes are the left-most min of their subarray:
 * p[0] = p[2] = 1
 * p[6] = 8
 * p[1] = p[8] = p[10] = 5
 * p[5] = 11 = n (root)
 *
 * indexes 3, 4, 7, 9 are not nodes; here p maps i to left-most min in their subarray:
 * p[3] = p[4] = 1
 * p[7] = 6
 * p[9] = 5
 *
 * @code{.cpp}
       auto ri = mono_st(a, less_equal()), p = cart_k_ary_tree(a, ri); // min cart tree
       auto ri = mono_st(a, greater_equal()), p = cart_k_ary_tree(a, ri); // max cart tree
       bool is_node = (p[i] > i || a[i] != a[p[i]]);
 * @endcode
 *
 * @param a,ri array and its monotonic stack
 * @returns parent array
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
template <class T> vector<int> cart_k_ary_tree(const vector<T>& a, const vector<int>& ri) {
	vector<int> p(ri);
	for (int i = 0; i < ssize(a); i++)
		for (int j = i + 1; j != ri[i]; j = ri[j])
			if (ri[j] == ri[i] || a[i] == a[ri[j]])
				p[j] = (p[i] > i || a[i] != a[p[i]] ? i : p[i]);
	return p;
}
/**
 * @see https://github.com/kth-competitive-programming/kactl /blob/main/content/strings/SuffixArray.h
 *
 * suffixes of "banana":
 * 0 banana 3
 * 1 anana  2
 * 2 nana   5
 * 3 ana    1
 * 4 na     4
 * 5 a      0
 *
 * 5 a      0
 * 3 ana    1
 * 1 anana  2
 * 0 banana 3
 * 4 na     4
 * 2 nana   5
 *
 * sa = {5, 3, 1, 0, 4, 2}
 * sa_inv = {3, 2, 5, 1, 4, 0} (sa[sa_inv[i]] == i, sa_inv[sa[i]] == i)
 *
 * @code{.cpp}
       string s;
       auto [sa, sa_inv] = get_sa(s, 256);
       // or
       vector<int> a;
       auto [sa, sa_inv] = get_sa(a, 100'005);
 * @endcode
 *
 * @param s,max_val string/array with 0 <= s[i] < max_val
 * @returns sa, sa_inv
 * @time O((n log n) + max_val)
 * @space this function allocates O(n) space for `sa`, `sa_inv`
 * vectors, but also allocates a O(max_val) vector `freq` temporarily
 */
template <class T> array<vector<int>, 2> get_sa(const T& s, int max_val) {
	int n = ssize(s);
	vector<int> sa(n), sa_inv(begin(s), end(s)), tmp(n);
	iota(begin(sa), end(sa), 0);
	for (int ln = 0; ln < n; ln = max(1, 2 * ln)) {
		iota(begin(tmp), begin(tmp) + ln, n - ln);
		copy_if(begin(sa), end(sa), begin(tmp) + ln, [&](int& val) {return (val -= ln) >= 0;});
		vector<int> freq(max_val);
		for (int val : sa_inv) freq[val]++;
		partial_sum(begin(freq), end(freq), begin(freq));
		for_each(rbegin(tmp), rend(tmp), [&](int t) {sa[--freq[sa_inv[t]]] = t;});
		swap(sa_inv, tmp);
		max_val = 1, sa_inv[sa[0]] = 0;
		auto prev_inv = [&](int i) {return pair(tmp[i], i + ln < n ? tmp[i + ln] : -1);};
		for (int i = 1; i < n; i++) {
			max_val += prev_inv(sa[i - 1]) != prev_inv(sa[i]);
			sa_inv[sa[i]] = max_val - 1;
		}
		if (max_val == n) break;
	}
	return {sa, sa_inv};
}
/**
 * @see https://github.com/kth-competitive-programming/kactl /blob/main/content/strings/SuffixArray.h
 *
 * suffixes of "banana", sorted:
 * a
 * |      1
 * ana
 * |||    3
 * anana
 *        0
 * banana
 *        0
 * na
 * ||     2
 * nana
 *
 * lcp = {1, 3, 0, 0, 2}
 *
 * @code{.cpp}
       string s;
       auto [sa, sa_inv] = get_sa(s, 256);
       vector<int> lcp = get_lcp_array(sa, sa_inv, s);
       // or
       vector<int> a;
       auto [sa, sa_inv] = get_sa(a, 100'005);
       vector<int> lcp = get_lcp_array(sa, sa_inv, a);
 * @endcode
 *
 * @param sa,sa_inv,s string/array and its suffix array
 * @returns lcp vector
 * @time O(n)
 * @space this function allocates O(n) space for `lcp`
 */
template <class T> vector<int> get_lcp_array(const vector<int>& sa, const vector<int>& sa_inv, const T& s) {
	int n = ssize(s);
	vector<int> lcp(max(0, n - 1));
	for (int i = 0, sz = 0; i < n; i++) {
		if (sz > 0) sz--;
		if (sa_inv[i] == 0) continue;
		for (int j = sa[sa_inv[i] - 1]; max(i, j) + sz < n && s[i + sz] == s[j + sz];) sz++;
		lcp[sa_inv[i] - 1] = sz;
	}
	return lcp;
}
const int mn = '0', max_val = 36; // mn <= s[i] < mn + max_val; for lowercase letters: mn = 'a', max_val = 26
/**
 * @see Replacing suffix trees with enhanced suffix arrays by Mohamed Ibrahim
 * Abouelhoda, Stefan Kurtz, Enno Ohlebusch
 *
 * offline version of suffix tree, idea: min k-ary cartesian tree of LCP array
 * corresponds exactly to the internal nodes of the suffix tree. Then add in <=
 * n nodes, one for each suffix, and it corresponds to the suffix tree.
 *
 * string = "cabcabacaabc"
 *                                              c
 *              c                               b
 *              b               c               a
 *              a               b           c   a
 *      c       a               a           b   c
 *      b       c       c       a           a   a
 *      a       a   c   b       c           a   b
 *      a       b   b   a       a       c   c   a
 *  c   c       a   a   a       b       b   a   c
 *  b   a   c | c   a   c       a       a   b | b
 *  a   b | b | b   c   a   c | c       a | a | a
 *  a | a | a | a | a   b | b | b   c | c | c | c
 *    1   2   3   1   0   1   2   0   1   2   3   <- LCP
 * (------------------R--------------------------)
 * (--a--------------) (--b------) (--c----------)
 * (a) (--b------) (c) (a) (--c--)     (--a------)
 *     (a) (--c--)             (a)     (a) (--b--)
 *             (a)                         (a) (c)
 *
 * note leaf nodes dont exist when that suffix is a prefix of a longer suffix
 *
 * @code{.cpp}
       string s;
       lcp_tree lt(s);
 * @endcode
 *
 * internal nodes are a subset of [0, n - 1), each internal node represents:
 *     - a prefix of some suffix; in the suffix tree, each edge has some substring. This prefix of suffix corresponds to this substring
 *     - a range in the suffix array
 *     - a lcp value of this range of suffixes representing length of prefix of these suffixes
 * leaf nodes are a subset of [n - 1, 2 * n - 1), each leaf represents:
 *     - a single suffix
 */
struct lcp_tree {
	int n, root;
	vector<int> sa, sa_inv, lcp, le, ri;
	vector<vector<int>> adj;
	/**
	 * @param s non-empty string/array
	 * @time O((n log n) + (n * max_val))
	 * @space adj is O(n * max_val)
	 */
	lcp_tree(const string& s) : n(ssize(s)), adj(max(n - 1, 0), vector(max_val, -1)) {
		assert(n > 0);
		auto ret = get_sa(s, mn + max_val);
		sa = ret[0], sa_inv = ret[1];
		lcp = get_lcp_array(sa, sa_inv, s);
		ri = mono_st(lcp, less_equal());
		le = mono_range(ri);
		auto p = cart_k_ary_tree(lcp, ri);
		root = find(begin(p), end(p), ssize(p)) - begin(p);
		auto node = [&](int i) -> int {
			return p[i] > i || lcp[i] != lcp[p[i]] ? i : p[i];
		};
		for (int i = 0; i < ssize(p); i++)
			if (node(i) == i && i != root) adj[p[i]][s[sa[i] + lcp[p[i]]] - mn] = i;
		for (int i = 0; i < n; i++) {
			int prev_lcp = (i ? lcp[i - 1] : -1);
			int next_lcp = (i < ssize(lcp) ? lcp[i] : 0);
			int u = (prev_lcp < next_lcp ? i : node(i - 1));
			int idx = sa[i] + max(prev_lcp, next_lcp);
			if (u == ssize(adj) || idx == n) continue;
			adj[u][s[idx] - mn] = ssize(lcp) + i;
		}
	}
	/**
	 * @param u node
	 * @returns range [le, ri) such that the following (ri - le) substrings are equal:
	 *     - for all i in [le, ri): s.substr(sa[i], lcp_len(u))
	 * @time O(1)
	 * @space O(1)
	 */
	inline array<int, 2> sa_range(int u) {
		if (u < n - 1) return {le[u] + 1, ri[u] + 1};
		return {u - n + 1, u - n + 2};
	}
	/**
	 * @param u node
	 * @returns length of longest common prefix of u's interval
	 * @time O(1)
	 * @space O(1)
	 */
	inline int lcp_len(int u) {
		return u < n - 1 ? lcp[u] : n - sa[u - n + 1];
	}
	/**
	 * @param u node
	 * @param c letter (don't subtract mn)
	 * @returns child of u following edge with label c, -1 means child doesn't exist
	 * @time O(1)
	 * @space O(1)
	 */
	inline int get_child(int u, char c) {
		return u < n - 1 ? adj[u][c - mn] : -1;
	}
};
