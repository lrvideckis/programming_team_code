#define PROBLEM "https://judge.yosupo.jp/problem/static_range_frequency"
#include "../../template.h"

#include "../../../Library/range_data_structures/seldom_used/mergeSortTree.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int n, q;
	cin >> n >> q;

	if(n == 0) {
		while(q--) {
			int l, r, x;
			cin >> l >> r >> x;
			cout << 0 << endl;
		}
		return 0;
	}

	vector<int> arr(n);
	for(int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	MergeSortTree mst(arr);

	while(q--) {
		int l, r, x;
		cin >> l >> r >> x;
		r--;
		if(l > r) {
			cout << 0 << endl;
		} else {
			cout << mst.query(l, r, x+1) - mst.query(l, r, x) << endl;
		}
	}

	return 0;
}
