#pragma once
//mnemonic: Binary Indexed Tree
//NOLINTNEXTLINE(readability-identifier-naming)
template<class T> struct BIT {
	const int N;
	vector<T> bit;
	BIT(int a_n) : N(a_n), bit(N + 1, 0) {}
	BIT(const vector<T>& a) : N(ssize(a)), bit(N + 1, 0) {
		for (int i = 1; i <= N; i++) {
			bit[i] += a[i - 1];
			int j = i + (i & -i);
			if (j <= N) bit[j] += bit[i];
		}
	}
	void update(int i, const T& d) {
		assert(0 <= i && i < N);
		for (i++; i <= N; i += i & -i) bit[i] += d;
	}
	T sum(int r) const {//sum of range [0, r)
		assert(0 <= r && r <= N);
		T ret = 0;
		for (; r; r -= r & -r) ret += bit[r];
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
			if (pos + pw <= N && bit[pos + pw] < sum)
				pos += pw, sum -= bit[pos];
		return pos + 1;
	}
};
