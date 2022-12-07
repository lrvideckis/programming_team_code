#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "../template.hpp"

#include "../../../library/range_data_structures/sparse_table.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<int> arr(n);
	vector<pair<int, int>> init(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		init[i] = {arr[i], i};
	}
	RMQ<pair<int, int>> rmq(init, [](auto x, auto y) {
		return min(x, y);
	});
	while (q--) {
		int l, r;
		cin >> l >> r;
		auto [mn, idxMn] = rmq.query(l, r);
		assert(l <= idxMn && idxMn < r && arr[idxMn] == mn);
		cout << mn << '\n';
	}
}
