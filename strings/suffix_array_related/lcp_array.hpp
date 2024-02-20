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
