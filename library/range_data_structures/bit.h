#pragma once
//library checker tests: https://judge.yosupo.jp/problem/point_add_range_sum, https://judge.yosupo.jp/problem/vertex_add_path_sum, https://judge.yosupo.jp/problem/vertex_add_subtree_sum, https://judge.yosupo.jp/problem/predecessor_problem
//mnemonic: Binary Indexed Tree
//NOLINTNEXTLINE(readability-identifier-naming)
template<class T> struct BIT {
	const int n;
	vector<T> bit;
	BIT(int a_n) : n(a_n), bit(n + 1, 0) {}
	BIT(const vector<T>& a) : n(a.size()), bit(n + 1, 0) {
		for (int i = 1; i <= n; i++) {
			bit[i] += a[i - 1];
			int j = i + (i & -i);
			if (j <= n) bit[j] += bit[i];
		}
	}
	void update(int i, const T& d) {
		assert(0 <= i && i < n);
		for (i++; i <= n; i += i & -i) bit[i] += d;
	}
	T sum(int r) const {//sum of range [0, r)
		assert(0 <= r && r <= n);
		T ret = 0;
		for (; r; r -= r & -r) ret += bit[r];
		return ret;
	}
	T sum(int l, int r) const {//sum of range [l, r)
		assert(0 <= l && l <= r && r <= n);
		return sum(r) - sum(l);
	}
	//Returns min pos such that sum of [0, pos) >= sum
	//Returns n + 1 if no sum is >= sum, or 0 if empty sum is.
	//Doesn't work with negatives
	int lower_bound(T sum) const {
		if (sum <= 0) return 0;
		int pos = 0;
		for (int pw = 1 << (31 - __builtin_clz(n | 1)); pw; pw >>= 1) {
			if (pos + pw <= n && bit[pos + pw] < sum)
				pos += pw, sum -= bit[pos];
		}
		return pos + 1;
	}
};
