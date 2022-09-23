#pragma once
//mnemonic: Binary Indexed Tree
//NOLINTNEXTLINE(readability-identifier-naming)
template<class T> struct BIT {
	const int N;
	vector<T> bit;
	BIT(int a_n) : N(a_n), bit(N, 0) {}
	BIT(const vector<T>& a) : N(ssize(a)), bit(a) {
		for (int i = 0; i < N; i++) {
			int j = i | (i + 1);
			if (j < N) bit[j] += bit[i];
		}
	}
	void update(int i, const T& d) {
		assert(0 <= i && i < N);
		for (; i < N; i |= i + 1) bit[i] += d;
	}
	T sum(int r) const {//sum of range [0, r)
		assert(0 <= r && r <= N);
		T ret = 0;
		for (; r > 0; r &= r - 1) ret += bit[r - 1];
		return ret;
	}
	T sum(int l, int r) const {//sum of range [l, r)
		assert(0 <= l && l <= r && r <= N);
		return sum(r) - sum(l);
	}
	//Returns min pos (0<=pos<=N+1) such that sum of [0, pos) >= sum
	//Returns N + 1 if no sum is >= sum, or 0 if empty sum is.
	//Doesn't work with negatives
	int lower_bound(T sum) const {
		if (sum <= 0) return 0;
		int pos = 0;
		for (int pw = 1 << __lg(N | 1); pw; pw >>= 1)
			if (pos + pw <= N && bit[pos + pw - 1] < sum)
				pos += pw, sum -= bit[pos - 1];
		return pos + 1;
	}
};
