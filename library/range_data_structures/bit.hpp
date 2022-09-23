#pragma once
//mnemonic: Binary Indexed Tree
//NOLINTNEXTLINE(readability-identifier-naming)
template<class T> struct BIT {
	vector<T> bit;
	BIT(int n) : bit(n, 0) {}
	BIT(const vector<T>& a) : bit(a) {
		for (int i = 0; i < ssize(a); i++) {
			int j = i | (i + 1);
			if (j < ssize(a)) bit[j] += bit[i];
		}
	}
	void update(int i, const T& d) {
		assert(0 <= i && i < ssize(bit));
		for (; i < ssize(bit); i |= i + 1) bit[i] += d;
	}
	T sum(int r) const {//sum of range [0, r)
		assert(0 <= r && r <= ssize(bit));
		T ret = 0;
		for (; r > 0; r &= r - 1) ret += bit[r - 1];
		return ret;
	}
	T sum(int l, int r) const {//sum of range [l, r)
		assert(0 <= l && l <= r && r <= ssize(bit));
		return sum(r) - sum(l);
	}
	//Returns min pos (0<=pos<=ssize(bit)+1) such that sum of [0, pos) >= sum
	//Returns ssize(bit) + 1 if no sum is >= sum, or 0 if empty sum is.
	//Doesn't work with negatives
	int lower_bound(T sum) const {
		if (sum <= 0) return 0;
		int pos = 0;
		for (int pw = 1 << __lg(ssize(bit) | 1); pw; pw >>= 1)
			if (pos + pw <= ssize(bit) && bit[pos + pw - 1] < sum)
				pos += pw, sum -= bit[pos - 1];
		return pos + 1;
	}
};
