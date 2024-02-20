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
const int mn = '0', max_val = 36; // mn <= s[i] < mn + max_val; for lowercase letters: mn = 'a', max_val = 26
/**
 * Burrows Wheeler transform
 */
struct find_bwt {
	int n;
	char last;
	vector<array<int, max_val>> occ;
	array < int, max_val + 1 > cnt{};
	/**
	 * @code{.cpp}
	       string s;
	       auto [sa, sa_inv] = get_sa(s, 256);
	       find_bwt fb(s, sa);
	 * @endcode
	 * @param s,sa a string and its suffix array
	 * @time O(n * max_val)
	 * @space O(n * max_val) for `occ` vector; it's possible to improve this
	 *     to O(n * max_val / 64) https://codeforces.com/contest/963/submission/217802614
	 */
	find_bwt(const string& s, const vector<int>& sa) : n(ssize(s)), last(empty(s) ? -1 : s.back() - mn), occ(n + 1) {
		for (int i = 0; i < n; i++) {
			cnt[s[i] + 1 - mn]++;
			occ[i + 1] = occ[i];
			if (sa[i] == 0) continue;
			occ[i + 1][s[sa[i] - 1] - mn]++;
		}
		partial_sum(begin(cnt), end(cnt), begin(cnt));
	}
	/**
	 * @code{.cpp}
	       string t;
	       auto [le, ri] = fb.find_str(t);
	 * @endcode
	 * @param t query string
	 * @returns vectors `le`, `ri` where given `t_le` (0 <= t_le <= |t|) defines a suffix [t_le, |t|) of t:
	 *     - for all i in [le[t_le], ri[t_le]): t.substr(t_le) == s.substr(sa[i], ssize(t) - t_le)
	 *     - `ri[t_le] - le[t_le]` is the # of matches of t.substr(t_le) in s.
	 *     note: ri[t_le] - le[t_le] <= ri[t_le + 1] - le[t_le + 1]
	 * @time O(|t|)
	 * @space 2 O(|t|) vectors are allocated and returned
	 */
	array<vector<int>, 2> find_str(const string& t) {
		vector<int> le(ssize(t) + 1, 0), ri(ssize(t) + 1, n);
		for (int i = ssize(t) - 1; i >= 0; i--) {
			char c = t[i] - mn;
			le[i] = cnt[c] + occ[le[i + 1]][c] + (c == last && i < ssize(t) - 1);
			ri[i] = cnt[c] + occ[ri[i + 1]][c] + (c == last);
		}
		return {le, ri};
	}
};
