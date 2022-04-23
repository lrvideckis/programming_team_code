#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"
#include "../../stress-tests/test_utilities/template.h"

#include "../../content/range_data_structures/kth_smallest.h"

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
		cout << st.query(l, r-1, k+1) << endl;
	}
	return 0;
}
