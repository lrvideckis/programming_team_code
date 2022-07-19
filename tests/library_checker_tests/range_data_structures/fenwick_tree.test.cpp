#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "../../template.h"

#include "../../../library/range_data_structures/bit.h"
#include "../../../library/range_data_structures/simple_seg_tree.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<long long> arr(n);
	for(int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	BIT<long long> ft(arr);
	simple_seg_tree st(arr);
	while(q--) {
		int type;
		cin >> type;
		if(type == 0) {
			int p, x;
			cin >> p >> x;
			ft.update(p, x);
			st.update(p, x);
		} else {
			int l, r;
			cin >> l >> r;
			long long sum = ft.sum(l, r);
			assert(sum == st.query(l, r));
			cout << sum << endl;
		}
	}
	return 0;
}
