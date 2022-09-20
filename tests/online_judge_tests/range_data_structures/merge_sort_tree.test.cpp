#define PROBLEM "https://judge.yosupo.jp/problem/static_range_frequency"
#include "../../template.hpp"

#include "../../../library/range_data_structures/uncommon/merge_sort_tree.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<int> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	merge_sort_tree mst(arr);
	while (q--) {
		int l, r, x;
		cin >> l >> r >> x;
		cout << mst.query(l, r, x + 1) - mst.query(l, r, x) << endl;
	}
	return 0;
}
