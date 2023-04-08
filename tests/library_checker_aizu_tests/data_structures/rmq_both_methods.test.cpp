#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "../template.hpp"

#include "../../../library/data_structures/sparse_table.hpp"
#include "../../../library/data_structures/uncommon_range_data_structures/linear_rmq.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<int> arr(n);
	for (int i = 0; i < n; i++) cin >> arr[i];
	linear_rmq<int> lin_rmq(arr, less{});
	RMQ<int> rmq(arr, [&](auto x, auto y) { return min(x, y); });
	while (q--) {
		int le, ri;
		cin >> le >> ri;
		int idx_mn = lin_rmq.query_idx(le, ri);
		assert(le <= idx_mn && idx_mn < ri && arr[idx_mn] == rmq.query(le, ri));
		cout << arr[idx_mn] << '\n';
	}
}
