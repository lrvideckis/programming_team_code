#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "../../stress-tests/test_utilities/template.h"

#include "../../content/range_data_structures/sparseTable.h"

int main() {
	cin.tie(0)->sync_with_stdio(false);
	int n,q;
	cin >> n >> q;
	vector<int> arr(n);
	for(int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	sparseTable<int> st(arr, [](int x, int y) { return min(x, y); });
	while(q--) {
		int l,r;
		cin >> l >> r;
		cout << st.query(l,r-1) << endl;
	}
}
