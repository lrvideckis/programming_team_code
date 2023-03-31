#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"
#include "../template.hpp"

#include "../../../library/data_structures/uncommon_range_data_structures/kth_smallest.hpp"

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
			mx = max(mx, arr[j - 1]);
			assert(st.query(i, j, j - i - 1) == mx);
		}
	}
	while (q--) {
		int l, r, k;
		cin >> l >> r >> k;
		cout << st.query(l, r, k) << '\n';
	}
	return 0;
}
