#pragma once
//library checker tests: https://judge.yosupo.jp/problem/point_add_range_sum, https://judge.yosupo.jp/problem/vertex_add_path_sum, https://judge.yosupo.jp/problem/vertex_add_subtree_sum, https://judge.yosupo.jp/problem/predecessor_problem
//mnemonic: Binary Indexed Tree
//NOLINTNEXTLINE(readability-identifier-naming)
template<class T> struct BIT {
	vector<T> bit;
	BIT(int n) : bit(n, 0) {}
	BIT(const vector<T>& a) : bit(a.size()) {
		if (a.empty()) return;
		bit[0] = a[0];
		for (int i = 1; i < (int)a.size(); i++)
			bit[i] = bit[i - 1] + a[i];
		for (int i = (int)a.size() - 1; i > 0; i--) {
			int lower_i = (i & (i + 1)) - 1;
			if (lower_i >= 0)
				bit[i] -= bit[lower_i];
		}
	}
	void update(int idx, const T& d) {
		for (; idx < (int)bit.size(); idx |= idx + 1)
			bit[idx] += d;
	}
	T sum(int r) const {//sum of range [0, r)
		T ret = 0;
		for (; r > 0; r &= r - 1)
			ret += bit[r - 1];
		return ret;
	}
	T sum(int l, int r) const {//sum of range [l, r)
		return sum(r) - sum(l);
	}
	//Returns min pos such that sum of [0, pos] >= sum
	//Returns bit.size() if no sum is >= sum, or -1 if empty sum is.
	//Doesn't work with negatives (since it's greedy), counterexample: array: {1, -1}, sum: 1, this returns 2, but should return 0
	int lower_bound(T sum) const {
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << (31 - __builtin_clz(bit.size() | 1)); pw; pw >>= 1) {
			if (pos + pw <= (int)bit.size() && bit[pos + pw - 1] < sum)
				pos += pw, sum -= bit[pos - 1];
		}
		return pos;
	}
};
