#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "../../template.h"

#include "../../content/range_data_structures/fenwickTree.h"

int main() {
	cin.tie(0)->sync_with_stdio(false);
	int n,q;
	cin >> n >> q;
	vector<ll> arr(n);
	for(int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	fenwickTree<ll> ft(arr);
	while(q--) {
		int type;
		cin >> type;
		if(type == 0) {
			int p, x;
			cin >> p >> x;
			ft.update(p,x);
		} else {
			int l,r;
			cin >> l >> r;
			cout << ft.sum(l,r-1) << endl;
		}
	}
	return 0;
}
