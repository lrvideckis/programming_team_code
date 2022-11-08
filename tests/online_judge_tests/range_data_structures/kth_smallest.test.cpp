#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"
#include "../template.hpp"

#include "../../../library/range_data_structures/uncommon/kth_smallest.hpp"
#include "../../../library/range_data_structures/uncommon/merge_sort_tree.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<int> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	vector<int> sorted(arr);
	sort(sorted.begin(), sorted.end());
	sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
	kth_smallest st(arr);
	for (int i = 0; i < n; i++) {
		int mx = arr[i];
		for (int j = i + 1; j <= min(i + 5, n); j++) {
			assert(st.query(i, j, j - i - 1) == mx);
			mx = max(mx, arr[j]);
		}
	}
	merge_sort_tree mst(arr);
	while (q--) {
		int l, r, k;
		cin >> l >> r >> k;
		int res = st.query(l, r, k);
		cout << res << endl;
		int start = 0, end = ssize(sorted);
		while (start + 1 < end) {
			int mid = start + (end - start) / 2;
			if (mst.query(l, r, sorted[mid]) <= k)
				start = mid;
			else
				end = mid;
		}
		assert(res == sorted[start]);
	}
	return 0;
}
