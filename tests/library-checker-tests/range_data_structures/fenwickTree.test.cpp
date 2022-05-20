#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "../../template.h"

#include "../../../Library/range_data_structures/seldom_used/fenwickInv.h"

int main() {
	cin.tie(0)->sync_with_stdio(false);
	int n, q;
	cin >> n >> q;
	vector<long long> arr(n);
	for(int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	fenwickTree<long long> ft(arr);

	vector<long long> init(arr);
	for(int i = n-2; i >= 0; i--) init[i] += init[i+1];
	fenwickInv<long long> ftInv(init);
	while(q--) {
		int type;
		cin >> type;
		if(type == 0) {
			int p, x;
			cin >> p >> x;
			ft.update(p, x);
			ftInv.update(0, p, x);
		} else {
			int l,r;
			cin >> l >> r;
			r--;
			long long res = ft.sum(l, r);
			assert(res == ftInv.query(l) - (r+1<n?ftInv.query(r+1):0));
			cout << res << endl;
		}
	}
	return 0;
}
