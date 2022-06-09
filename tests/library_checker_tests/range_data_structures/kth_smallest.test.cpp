#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"
#include "../../template.h"

#include "../../../Library/range_data_structures/seldom_used/kth_smallest.h"
#include "../../../Library/range_data_structures/seldom_used/mergeSortTree.h"

int main() {
	cin.tie(0)->sync_with_stdio(false);

	int n,q;
	cin >> n >> q;
	vector<int> arr(n);
	for(int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	vector<int> sorted(arr);
	sort(sorted.begin(), sorted.end());
	sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());

	kth_smallest st(arr);
	MergeSortTree mst(arr);

	while(q--) {
		int l,r,k;
		cin >> l >> r >> k;
		r--;

		int res = st.query(l, r, k);
		cout << res << endl;

		int start = 0, end = sorted.size();
		while(start + 1 < end) {
			int mid = (start+end)/2;
			if(mst.query(l, r, sorted[mid]) <= k) {
				start = mid;
			} else end = mid;
		}
		assert(res == sorted[start]);
	}
	return 0;
}
