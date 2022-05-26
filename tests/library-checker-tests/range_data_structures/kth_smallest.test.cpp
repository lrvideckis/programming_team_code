#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"
#include "../../template.h"

#include "../../../Library/range_data_structures/seldom_used/kth_smallest.h"

int main() {
	cin.tie(0)->sync_with_stdio(false);
	int n,q;
	cin >> n >> q;
	vector<int> arr(n);
	for(int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	kth_smallest st(arr);
	while(q--) {
		int l,r,k;
		cin >> l >> r >> k;
		cout << st.query(l, r-1, k) << endl;
	}
	return 0;
}
