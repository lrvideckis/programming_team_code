#pragma once
//NOLINTNEXTLINE(readability-identifier-naming)
template <typename T> struct BIT {
	vector<T> bit;
	BIT(int n) : bit(n, 0) {}
	BIT(const vector<T>& a) : bit(a) {
		for (int i = 0; i < ssize(a); i++) {
			int j = i | (i + 1);
			if (j < ssize(a))
				bit[j] += bit[i];
		}
	}
	void update(int i, const T& d) {
		assert(0 <= i && i < ssize(bit));
		for (; i < ssize(bit); i |= i + 1)
			bit[i] += d;
	}
	/**
	 * @brief Returns sum of range [0, ri)
	 * @time O(log n)
	 */
	T sum(int ri) const {
		assert(0 <= ri && ri <= ssize(bit));
		T ret = 0;
		for (; ri > 0; ri &= ri - 1)
			ret += bit[ri - 1];
		return ret;
	}
	/**
	 * @brief Returns sum of range [le, ri)
	 * @time O(log n)
	 */
	T sum(int le, int ri) const {
		assert(0 <= le && le <= ri && ri <= ssize(bit));
		return sum(ri) - sum(le);
	}
	/**
	 * @brief Returns min pos such that sum of [0, pos) >= sum. Returns
	 *     ssize(bit) + 1 if no sum is >= sum.
	 * @note Doesn't work if BIT::sum(i, i + 1) < 0
	 * @time O(log n)
	 */
	int lower_bound(T sum) const {
		if (sum <= 0)
			return 0;
		int pos = 0;
		for (int pw = 1 << __lg(ssize(bit) | 1); pw; pw >>= 1)
			if (pos + pw <= ssize(bit) && bit[pos + pw - 1] < sum)
				pos += pw, sum -= bit[pos - 1];
		return pos + 1;
	}
};
