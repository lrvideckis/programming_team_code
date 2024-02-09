#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"

#include "../../../library/data_structures/bit_uncommon/rupq.hpp"
#include "../../../library/data_structures/bit_uncommon/rurq.hpp"
#include "../../../library/data_structures/bit_uncommon/lower_bound.hpp"
#include "../../../library/data_structures/seg_tree_uncommon/lower_bound.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<long long> arr(n);
	vector<int> arr_int(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		arr_int[i] = int(arr[i]);
	}
	BIT<long long> bit(arr);
	seg_tree st(arr_int);
	bit_rurq<long long> bit_rr(arr);
	vector<long long> suf_sum(n);
	partial_sum(rbegin(arr), rend(arr), rbegin(suf_sum));
	bit_rupq<long long> bit_i(suf_sum);
	for (int i = 0; i < n; i++) {
		auto curr_1 = bit.sum(i, i + 1);
		assert(arr[i] == curr_1);
		auto curr_2 = bit_i.get_index(i);
		auto curr_3 = bit.sum(i, n);
		assert(curr_2 == curr_3);
		auto curr_4 = bit_i.get_index(i);
		assert(curr_4 == suf_sum[i]);
	}
	while (q--) {
		int type;
		cin >> type;
		if (type == 0) {
			int p, x;
			cin >> p >> x;
			bit.update(p, x);
			st.update(p, p + 1, x);
			bit_rr.update(p, p + 1, x);
			bit_i.update(0, p + 1, x);
		} else {
			int l, r;
			cin >> l >> r;
			long long res = bit.sum(l, r);
			{
				long long bit_i_result = bit_i.get_index(l);
				if (r < n) bit_i_result -= bit_i.get_index(r);
				assert(res == bit_i_result);
			}
			auto curr_res = bit_rr.sum(l, r);
			assert(res == curr_res);
			cout << res << '\n';
		}
		auto sum = get_rand<long long>(0LL, (long long)(1e12));
		int pos_bit = lower_bound(bit, sum);
		int pos_st = lower_bound(st, sum);
		assert(pos_bit == pos_st);
	}
	return 0;
}
