/**
 * Binary Indexed Tree
 */
template <class T> struct BIT {
	vector<T> s;
	BIT() {}
	/**
	 * @param n initial size
	 * @time O(n)
	 * @space O(n) for `s` vector
	 */
	BIT(int n) : s(n) {}
	/**
	 * @param a initial array
	 * @time O(n)
	 * @space O(n) for `s` vector
	 */
	BIT(const vector<T>& a) : s(a) {
		for (int i = 0; i < ssize(a); i++) {
			int j = i | (i + 1);
			if (j < ssize(a)) s[j] += s[i];
		}
	}
	/**
	 * @param i index
	 * @param d delta
	 * @time O(log n)
	 * @space O(1)
	 */
	inline void update(int i, T d) {
		assert(0 <= i && i < ssize(s));
		for (; i < ssize(s); i |= i + 1) s[i] += d;
	}
	/**
	 * @param ri defines range [0, ri)
	 * @returns a[0] + a[1] + ... + a[ri - 1]
	 * @time O(log n)
	 * @space O(1)
	 */
	inline T sum(int ri) {
		assert(0 <= ri && ri <= ssize(s));
		T ret = 0;
		for (; ri > 0; ri &= ri - 1) ret += s[ri - 1];
		return ret;
	}
	/**
	 * @param le,ri defines range [le, ri)
	 * @returns a[le] + a[le + 1] + ... + a[ri - 1]
	 * @time O(log n)
	 * @space O(1)
	 */
	inline T sum(int le, int ri) {
		assert(le <= ri);
		return sum(ri) - sum(le);
	}
};
/**
 * Requires bit.sum(i, i + 1) >= 0
 * @param bit binary indexed tree
 * @param sum see return
 * @returns min pos such that sum of range [0, pos) >= sum (or n+1)
 * @time O(log n)
 * @space O(1)
 */
template <class T> inline int lower_bound(BIT<T>& bit, T sum) {
	if (sum <= 0) return 0;
	int pos = 0;
	for (int pw = 1 << __lg(ssize(bit.s) | 1); pw; pw >>= 1)
		if (pos + pw <= ssize(bit.s) && bit.s[pos + pw - 1] < sum)
			pos += pw, sum -= bit.s[pos - 1];
	return pos + 1;
}
