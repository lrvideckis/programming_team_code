#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "../template.hpp"

#include "../../../library/data_structures/uncommon_range_data_structures/disjoint_sparse_table.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<int> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	disjoint_rmq<int> rmq(arr, [](int x, int y) {
		return min(x, y);
	});
	while (q--) {
		int l, r;
		cin >> l >> r;
		cout << rmq.query(l, r) << '\n';
	}
}
