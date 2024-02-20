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
 * s = "baaba"
 *
 * even centers  1 3 5 7
 * string       b a a b a
 * odd centers  0 2 4 6 8
 *
 * @see https://codeforces.com/blog/entry/12143#comment-324162
 * @param s string/vector
 * @returns vector `man` where for center `i`:
 *     - substring [le, ri) has center (le + ri - 1)
 *     - substring [man[i], i - man[i] + 1) is longest palindrome around center
 *     - center i's longest palindrome has length = i - 2 * man[i] + 1
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
template <class T> vector<int> manacher(const T& s) {
	int n = ssize(s);
	vector<int> man(max(0, 2 * n - 1));
	for (int i = 0, p = 0; i < 2 * n - 1; i++) {
		int ri = i <= 2 * (p - man[p]) ? p - max(man[2 * p - i], man[p]) : i / 2;
		man[i] = i - ri;
		while (man[i] > 0 && ri + 1 < n && s[man[i] - 1] == s[ri + 1])
			man[i]--, ri++, p = i;
	}
	return man;
}
/**
 * queries for longest palindromic substring of a given substring
 */
template <class T> struct longest_pal_query {
	vector<int> man, idx;
	RMQ<int, function<int(int, int)>> rmq;
	/**
	 * @param s string/vector
	 * @time O(n log n)
	 * @space O(n log n) for rmq, everything else is O(n)
	 */
	longest_pal_query(const T& s) : man(manacher(s)), idx(ssize(s)) {
		iota(begin(idx), end(idx), 1);
		vector<int> init(ssize(man));
		iota(begin(init), end(init), 0);
		rmq = {init, [&](int i1, int i2) {return len(i1) < len(i2) ? i2 : i1;}};
	}
	/**
	 * @param i center
	 * @returns length of longest palindrome around center
	 * @time O(1)
	 * @space O(1)
	 */
	inline int len(int i) {return i - 2 * man[i] + 1;}
	/**
	 * approach: binary search: is there some palindromic substring with length >= mid ?
	 * note for a substring [le, ri) of s, the "relevant" centers are subarray [2 * le, 2 * ri - 1) of `man`
	 *
	 * when center i (in "relevant" range) is even (so represents an odd-length palindrome):
	 *     - i / 2 is index of middle of palindrome
	 *     - le <= i / 2 < ri
	 * when center i (in "relevant" range) is odd (so represents an even-length palindrome):
	 *     - (i - 1) / 2, (i + 1) / 2 are indexes of middles of palindrome
	 *     - le <= (i - 1) / 2 < (i + 1) / 2 < ri
	 *
	 * @param le,ri defines substring [le, ri) of s
	 * @returns {start index, length} of longest palindromic substring of s.substr(le, ri - le)
	 *     if there are multiple longest answers, this returns an arbitrary start index
	 * @time O(log n)
	 * @space O(1)
	 */
	inline array<int, 2> longest_pal(int le, int ri) {
		assert(0 <= le && le < ri && ri <= ssize(idx));
		int pal_len = lower_bound(begin(idx), begin(idx) + (ri - le), 0, [&](int mid, int) {
			return len(rmq.query(2 * le + mid - 1, 2 * ri - mid)) >= mid;
		}) - begin(idx);
		int best_center = rmq.query(2 * le + pal_len - 1, 2 * ri - pal_len);
		return {(best_center + 1 - pal_len) / 2, pal_len};
	}
};
