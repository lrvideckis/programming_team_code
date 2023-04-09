#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "../template.hpp"

#include "../../../library/data_structures/sparse_table.hpp"
#include "../../../library/data_structures/uncommon_data_structures/disjoint_sparse_table.hpp"
#include "../../../library/data_structures/uncommon_data_structures/linear_rmq.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<int> arr(n);
	for (int i = 0; i < n; i++) cin >> arr[i];
	RMQ<int> rmq(arr, [](auto x, auto y) {return min(x, y);});
	disjoint_rmq<int> dis_rmq(arr, [](auto x, auto y) {return min(x, y);});
	linear_rmq<int> lin_rmq(arr, less());
	while (q--) {
		int le, ri;
		cin >> le >> ri;
		int idx_min = lin_rmq.query_idx(le, ri);
		assert(le <= idx_min && idx_min < ri);
		assert(arr[idx_min] == rmq.query(le, ri));
		assert(arr[idx_min] == dis_rmq.query(le, ri));
		cout << arr[idx_min] << '\n';
	}
}
