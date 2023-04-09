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
		N(ssize(a_arr)),
		arr(a_arr),
		mask(1, vector<ull>(N)), less(a_less) {
		auto g = [&](int i) -> int {
			return idx.size() ? idx.back()[i << 6] : i;
		};
		while (1) {
			int n = ssize(mask.back());
			ull st = 0;
			vector<int> new_idx_row(n);
			for (int i = n - 1; i >= 0; i--) {
				while (st && less(arr[g(i)], arr[g(i + 1 + __builtin_ctzll(st))])) st &= st - 1;
				mask.back()[i] = st = ((st << 1) | 1);
				new_idx_row[i] = g(i + __lg(st));
			}
			idx.emplace_back(new_idx_row);
			if (n <= 2 * 64) break;
			mask.emplace_back((n + 63) >> 6);
		}
	}
	int f(int level, int i) const {
		return level ? idx[level - 1][i << 6] : i;
	}
	int min_idx_block(int level, int le, int ri) const {//returns index of min in range [le, ri)
		int x = 64 - (ri - le);
		assert(x > 0);
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
	/*
	void update(int idx, const T& val) {//time: theoretically O((log(n)^2) / log(log(n))), practically 4 * 64 array indexes
		//TODO
	}
	*/
};
