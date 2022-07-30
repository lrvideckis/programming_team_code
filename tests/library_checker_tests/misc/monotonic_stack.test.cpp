#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"
#include "../../template.h"

#include "../../../library/misc/monotonic_stack.h"
#include "../../../library/range_data_structures/rmq.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	RMQ<int> st(arr, [](int x, int y) {
		return min(x, y);
	});
	vector<int> left_lower = monotonic_stack(arr);
	reverse(arr.begin(), arr.end());
	vector<int> right_lower = monotonic_stack(arr);
	reverse(arr.begin(), arr.end());
	vector<int> par(n, -1);
	for (int i = 0; i < n; i++) {
		int l = left_lower[i], r = n - 1 - right_lower[n - 1 - i];
		assert(0 <= l + 1 && l + 1 <= i && i <= r - 1 && r - 1 < n);
		if (l + 1 < i) assert(st.query(l + 1, i) > arr[i]);
		if (i < r - 1) assert(st.query(i + 1, r) > arr[i]);
		if (l >= 0) assert(arr[l] <= arr[i]);
		if (r < n) assert(arr[r] <= arr[i]);
		if (l == -1 && r == n) par[i] = i;
		else if (l == -1) par[i] = r;
		else if (r == n) par[i] = l;
		else par[i] = arr[l] > arr[r] ? l : r;
	}
	for (int i = 0; i < n; i++)
		cout << par[i] << " ";
	return 0;
}
