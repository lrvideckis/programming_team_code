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
 * @code{.cpp}
       string s;
       vector<int> man(manacher(s));
       bool pal = is_pal(man, le, ri);
       // or
       vector<int> a;
       vector<int> man(manacher(a));
       bool pal = is_pal(man, le, ri);
 * @endcode
 *
 * @param man manacher array
 * @param le,ri defines substring [le,ri)
 * @returns 1 iff s.substr(le, ri - le) is a palindrome
 * @time O(1)
 * @space O(1)
 */
inline bool is_pal(const vector<int>& man, int le, int ri) {
	assert(0 <= le && le <= ri && ri <= (ssize(man) + 1) / 2);
	return (le == ri ? 1 : man[le + ri - 1] <= le);
}
/**
 * @see https://github.com/brunomaletta/Biblioteca /blob/master/Codigo/Strings/manacher.cpp
 *
 * @code{.cpp}
       string s;
       vector<int> man(manacher(s)), longest(longest_from_index(man));
       // or
       vector<int> a;
       vector<int> man(manacher(a)), longest(longest_from_index(man));
 * @endcode
 *
 * @param man manacher array
 * @returns longest where:
 *      - s.substr(i, i + longest[i]) is a palindrome
 *      - s.substr(i, i + j) is not a palindrome, if j > longest[i]
 * @time O(n)
 * @space an O(n) vector is allocated and returned
 */
vector<int> longest_from_index(const vector<int>& man) {
	int n = (ssize(man) + 1) / 2;
	vector longest(n, 1);
	for (int i = n - 2; i >= 0; i--) {
		longest[i] = min(longest[i + 1] + 2, n - i);
		while (!is_pal(man, i, i + longest[i])) longest[i]--;
	}
	return longest;
}
