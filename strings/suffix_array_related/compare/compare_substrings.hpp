/**
 * @code{.cpp}
       vector<int64_t> a;
       RMQ rmq(a, ranges::min); // -std=c++20
       RMQ rmq(a, [&](auto& x, auto& y) { return min(x, y); });
 * @endcode
 */
template <class T, class F> struct RMQ {
	vector<vector<T>> dp;
	F op;
	RMQ() {}
	/**
	 * @param a static array
	 * @param a_op any associative, communative, idempotent operation
	 * @time O(n log n)
	 * @space O(n log n) for `dp` vector
	 */
	RMQ(const vector<T>& a, F a_op) : dp(1, a), op(a_op) {
		for (int i = 0; (2 << i) <= ssize(a); i++) {
			dp.emplace_back(ssize(a) - (2 << i) + 1);
			transform(begin(dp[i]), end(dp[i]) - (1 << i), begin(dp[i]) + (1 << i), begin(dp[i + 1]), op);
		}
	}
	/**
	 * @param le,ri defines range [le, ri)
	 * @returns a[le] op a[le + 1] op ... op a[ri - 1]
	 * @time O(1)
	 * @space O(1)
	 */
	inline T query(int le, int ri) {
		assert(0 <= le && le < ri && ri <= ssize(dp[0]));
		int lg = __lg(ri - le);
		return op(dp[lg][le], dp[lg][ri - (1 << lg)]);
	}
};
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
/**
 * query for longest common prefix of 2 suffixes
 *
 * note if one of the suffixes is the entire string (i1 == 0 || i2 == 0)
 * then it's the same as z algorithm
 */
template <class T> struct lcp_query {
	vector<int> sa, sa_inv, lcp;
	RMQ<int, function<int(int, int)>> rmq;
	/**
	 * @param s,max_val string/array with 0 <= s[i] < max_val
	 * @time O((n log n) + max_val)
	 * @space O(n log n) for RMQ's; a O(max_val) vector `freq` is used temporarily during get_sa
	 */
	lcp_query(const T& s, int max_val) {
		auto ret = get_sa(s, max_val);
		sa = ret[0], sa_inv = ret[1];
		lcp = get_lcp_array(sa, sa_inv, s);
		rmq = {lcp, [](int x, int y) {return min(x, y);}};
	}
	/**
	 * @param i1,i2 defines substrings [i1, n), [i2, n), note passing i1,i2 = n is okay
	 * @returns max integer k such that s.substr(i1, k) == s.substr(i2, k)
	 * @time O(1)
	 * @space O(1)
	 */
	inline int get_lcp(int i1, int i2) {
		int n = ssize(sa);
		if (i1 > i2) swap(i1, i2);
		assert(0 <= i1 && i2 <= n);
		if (i1 == i2 || i2 == n) return n - i2;
		auto [le, ri] = minmax(sa_inv[i1], sa_inv[i2]);
		return rmq.query(le, ri);
	}
};
/**
 * @param lq lcp query struct
 * @param le1,ri1 first substring [le1, ri1)
 * @param le2,ri2 second substring [le2, ri2)
 * @returns a value `cmp` where:
 *     - cmp < 0 iff s.substr(le1, ri1 - le1) < s.substr(le2, ri2 - le2)
 *     - cmp = 0 iff s.substr(le1, ri1 - le1) = s.substr(le2, ri2 - le2)
 *     - cmp > 0 iff s.substr(le1, ri1 - le1) > s.substr(le2, ri2 - le2)
 * @time O(1)
 * @space O(1)
 */
template <class T> inline int substr_cmp(lcp_query<T>& lq,
        int le1, int ri1, int le2, int ri2) {
	assert(0 <= le1 && le1 <= ri1 && ri1 <= ssize(lq.sa));
	assert(0 <= le2 && le2 <= ri2 && ri2 <= ssize(lq.sa));
	int len1 = ri1 - le1;
	int len2 = ri2 - le2;
	return lq.get_lcp(le1, le2) >= min(len1, len2) ? len1 - len2 : lq.sa_inv[le1] - lq.sa_inv[le2];
}
