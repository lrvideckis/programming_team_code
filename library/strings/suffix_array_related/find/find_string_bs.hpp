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
 * Range of matches, and example of longest matching prefix of t in s
 */
struct match {
	/**
	 * t is some string defined by the query
	 *
	 * [sa_le, sa_ri) defines subarray of suffix array such that:
	 * - for all i in [sa_le, sa_ri): t == s.substr(sa[i], ssize(t))
	 * - `sa_ri - sa_le` is the # of matches of t in s.
	 *
	 * [str_le, str_ri) defines a substring of s such that:
	 * - s.substr(str_le, str_ri - str_le) == t.substr(0, str_ri - str_le)
	 * - (str_ri - str_le) is maximized, if there are multiple answers, str_le is arbitrary
	 *
	 * - note if sa_le < sa_ri, i.e. at least one match, then str_ri - str_le == ssize(t)
	 * - note if sa_le == sa_ri, i.e. no matches, then str_ri - str_le < ssize(t)
	 * @{
	 */
	int sa_le, sa_ri, str_le, str_ri;
	/** @} */
};
/**
 * @see https://github.com/yosupo06/Algorithm/blob /master/src/string/suffixarray.hpp
 * @param s,sa string/array and its suffix array
 * @param t query string
 * @returns see match
 * @time O(|t| * log(|s|))
 * @space O(1)
 */
template <class T> inline match find_str(const T& s, const vector<int>& sa, const T& t) {
	int str_le = 0, str_ri = 0;
	auto cmp = [&](int i, int cmp_val) -> bool {
		auto [it_s, it_t] = mismatch(begin(s) + i, end(s), begin(t), end(t));
		if (it_s - begin(s) - i > str_ri - str_le) str_le = i, str_ri = it_s - begin(s);
		if (it_s != end(s) && it_t != end(t)) return (*it_s) - (*it_t) < cmp_val;
		return cmp_val ^ (ssize(s) - i < ssize(t));
	};
	int sa_le = lower_bound(begin(sa), end(sa), 0, cmp) - begin(sa);
	int sa_ri = lower_bound(begin(sa) + sa_le, end(sa), 1, cmp) - begin(sa);
	return {sa_le, sa_ri, str_le, str_ri};
}
