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
 * range update, point query
 */
template <class T> struct bit_rupq {
	int n;
	BIT<T> bit;
	/**
	 * @param a_n size
	 * @time O(n)
	 * @space O(n)
	 */
	bit_rupq(int a_n) : n(a_n), bit(n) {}
	/**
	 * @param a initial array
	 * @time O(n)
	 * @space O(n)
	 */
	bit_rupq(vector<T> a) : n(ssize(a)) {
		adjacent_difference(begin(a), end(a), begin(a));
		bit = {a};
	}
	/**
	 * does a[le] += d, a[le + 1] += d, .., a[ri - 1] += d
	 *
	 * @param le,ri defines range [le, ri)
	 * @param d delta to add to all indexes in range
	 * @time O(log n)
	 * @space O(1)
	 */
	inline void update(int le, int ri, T d) {
		assert(0 <= le && le <= ri && ri <= n);
		if (le < n) bit.update(le, d);
		if (ri < n) bit.update(ri, -d);
	}
	/**
	 * @param i index
	 * @returns a[i]
	 * @time O(log n)
	 * @space O(1)
	 */
	inline T get_index(int i) {
		assert(0 <= i && i < n);
		return bit.sum(i + 1);
	}
};
