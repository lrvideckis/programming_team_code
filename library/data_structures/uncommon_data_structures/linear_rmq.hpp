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
	function<bool(const T&, const T&)> less; //any transitive compare operator
	vector<vector<int>> idx; //idx[level][i] = index of min in range [i, i + 64^(level+1))
	vector<vector<ull>> mask; //mask[level][le] = stack representing subarray arr[le, le + 64)
	//time & memory: O(n)
	linear_rmq(const vector<T>& a_arr, function<bool(const T&, const T&)> a_less) : N(ssize(a_arr)), arr(a_arr), less(a_less) {
		for (int n = N; n >= 2; n = ((n + 63) >> 6)) {
			int level = ssize(idx);
			idx.emplace_back(n);
			mask.emplace_back(n + 1);
			update(level, 0, n);
		}
	}
	void update(int level, int le, int ri) {
		for (int i = ri - 1; i >= le; i--) {
			ull st = mask[level][i + 1];
			const T& curr = arr[blk(level, i)];
			while (st && less(curr, arr[blk(level, i + 1 + __builtin_ctzll(st))])) st &= st - 1;
			mask[level][i] = st = ((st << 1) | 1);
			idx[level][i] = blk(level, i + int(__lg(st)));
		}
	}
	int blk(int level, int i) const {
		return level ? idx[level - 1][i << 6] : i;
	}
	int mn(int le, int ri) const {
		return less(arr[le], arr[ri]) ? le : ri;
	}
	int query_idx(int le, int ri) const {//time: theoretically O(log(n) / log(log(n))), practically if n <= 2^24 then ssize(mask) <= 4
		assert(0 <= le && le < ri && ri <= N);
		int res = le;
		for (int level = 0; le < ri && level < ssize(mask); level++, le = (le >> 6) + 1, ri = ((ri - 1) >> 6)) {
			if (ri - le < 64) {//TODO: avoid min_idx_block if it's the last block
				int x = 64 - (ri - le);
				return mn(res, blk(level, le + int(__lg((mask[level][le] << x) >> x))));
			}
			res = mn(res, mn(idx[level][le], idx[level][ri - 64]));
		}
		return res;
	}
	void set_val(int pos, const T& val) {//time: theoretically O((log(n)^2) / log(log(n)))
		assert(0 <= pos && pos < N);
		arr[pos] = val;
		for (int level = 0; level < ssize(mask); level++, pos >>= 6)
			update(level, max(0, pos - 63), pos + 1);
	}
};
