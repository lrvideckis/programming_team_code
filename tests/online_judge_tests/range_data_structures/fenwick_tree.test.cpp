#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "../template.hpp"

#include "../../../library/range_data_structures/bit.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<long long> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	BIT<long long> ft(arr);
	while (q--) {
		int type;
		cin >> type;
		if (type == 0) {
			int p, x;
			cin >> p >> x;
			ft.update(p, x);
		} else {
			int l, r;
			cin >> l >> r;
			cout << ft.sum(l, r) << endl;
		}
	}
	return 0;
}
