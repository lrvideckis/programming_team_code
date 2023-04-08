#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "../template.hpp"

#include "../../../library/data_structures/sparse_table.hpp"
#include "../../../library/data_structures/uncommon_data_structures/disjoint_sparse_table.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<int> arr(n);
	for (int i = 0; i < n; i++) cin >> arr[i];
	RMQ<int> rmq(arr, [](auto x, auto y) {return min(x, y);});
	disjoint_rmq<int> dis_rmq(arr, [](auto x, auto y) {return min(x, y);});
	while (q--) {
		int le, ri;
		cin >> le >> ri;
		int res = rmq.query(le, ri);
		assert(res == dis_rmq.query(le, ri));
		cout << res << '\n';
	}
}
