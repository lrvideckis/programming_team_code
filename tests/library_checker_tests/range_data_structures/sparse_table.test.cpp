#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "../../template.h"

#include "../../../library/range_data_structures/rmq.h"

int main() {
	cin.tie(0)->sync_with_stdio(false);
	int n,q;
	cin >> n >> q;
	vector<int> arr(n);
	vector<pair<int,int>> init(n);
	for(int i = 0; i < n; i++) {
		cin >> arr[i];
		init[i] = {arr[i], i};
	}
	RMQ<pair<int,int>> st(init, [](auto x, auto y) { return min(x, y); });
	while(q--) {
		int l,r;
		cin >> l >> r;
		auto [mn, idxMn] = st.query(l, r);
		assert(arr[idxMn] == mn);
		cout << mn << endl;
	}
}
