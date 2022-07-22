#define PROBLEM "https://judge.yosupo.jp/problem/static_range_frequency"
#include "../../template.h"
#include "../../random.h"

#include "../../../library/range_data_structures/uncommon/merge_sort_tree.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int n, q;
	cin >> n >> q;

	if(n == 0) {
		while(q--) cout << 0 << " ";
		return 0;
	}

	vector<int> arr(n);
	for(int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	merge_sort_tree mst(arr);

	while(q--) {
		int l, r, x;
		cin >> l >> r >> x;
		if(getRand(1, 2) == 1)
			cout << mst.query(l, r, x+1) - mst.query(l, r, x) << endl; //iterative
		else
			cout << mst.query(1, l, r, x+1) - mst.query(1, l, r, x) << endl; //recursive
	}

	return 0;
}
