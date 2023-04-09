/** @file */
#pragma once
//https://codeforces.com/blog/entry/78931
//https://codeforces.com/blog/entry/92310
//https://github.com/okwedook/olymp/blob/master/code/data-structures/LinearMinTable.hpp
//TODO: have least_common_ancestor.hpp depend on this
//TODO: prefer `less()` over `less{}` for documentation
template <typename T> struct linear_rmq {
	using ull = unsigned long long;
	const int N;
	vector<T> arr;
	vector<vector<int>> idx; //idx[level][i] = index of min in range [i, i + 64^(level+1))
	vector<vector<ull>> mask; //mask[level][le] = stack representing subarray arr[le, le + 64)


	function<bool(const T&, const T&)> less; //any transitive compare operator
	//time & memory: O(n)
	linear_rmq(const vector<T>& a_arr, function<bool(const T&, const T&)> a_less) :
		N(ssize(a_arr)), arr(a_arr), less(a_less) {
		for (int n = N; ; n = (n + 63) >> 6) {
			vector<int> new_idx(n);
			vector<ull> new_mask(n);
			ull st = 0;
			for (int i = n - 1; i >= 0; i--) {
				while (st && less(arr[f(ssize(idx), i)], arr[f(ssize(idx), i + 1 + __builtin_ctzll(st))])) st &= st - 1;
				new_mask[i] = st = ((st << 1) | 1);
				new_idx[i] = f(ssize(idx), i + __lg(st));
			}
			idx.emplace_back(new_idx);
			mask.emplace_back(new_mask);
			if (n <= 2 * 64) break;//TODO: move to for-loop condition
		}
	}
	int f(int level, int i) const {
		return level ? idx[level - 1][i << 6] : i;
	}
	int min_idx_block(int level, int le, int ri) const {//returns index of min in range [le, ri)
		int x = 64 - (ri - le);
		return f(level, le + __lg((mask[level][le] << x) >> x));
	}
	int min_ind(int le, int ri) const {
		return less(arr[le], arr[ri]) ? le : ri;
	}
	int query_idx(int le, int ri) const {//time: theoretically O(log(n) / log(log(n))), practically if n <= 2^24 then ssize(mask) <= 4
		assert(0 <= le && le < ri && ri <= N);
		int res = le;
		for (int level = 0; le < ri && level < ssize(mask); level++, le = (le >> 6) + 1, ri = ((ri - 1) >> 6)) {
			if (ri - le < 64) //TODO: avoid min_idx_block if it's the last block
				return min_ind(res, min_idx_block(level, le, ri));
			res = min_ind(res, min_ind(idx[level][le], idx[level][ri - 64]));
		}
		return res;
	}
	void update(int level, int le, int ri) {
		assert(0 <= le && le < ri && ri <= ssize(mask[level]));
		ull st = (ri < ssize(mask[level]) ? mask[level][ri] : 0);
		for (int i = ri - 1; i >= le; i--) {
			while (st && less(arr[f(level, i)], arr[f(level, i + 1 + __builtin_ctzll(st))])) st &= st - 1;
			mask[level][i] = st = ((st << 1) | 1);
			idx[level][i] = f(level, i + __lg(st));
		}
	}
	void set_val(int pos, const T& val) {//time: theoretically O((log(n)^2) / log(log(n)))
		assert(0 <= pos && pos < N);
		arr[pos] = val;
		for (int level = 0; level < ssize(mask); level++, pos >>= 6) {
			//int n = ssize(mask[level]);
			update(level, max(0, pos - 63), pos + 1);
		}
	}
};
