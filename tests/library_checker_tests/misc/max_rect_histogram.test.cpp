#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_3_C"
#include "../../template.h"

#include "../../../library/misc/monotonic_stack.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;
	vector<pair<int, int>> arr(n), arr_rev(n);

	auto rv /*reverse*/ = [&](int j) -> int {
		return n - 1 - j;
	};

	for (int i = 0; i < n; i++) {
		cin >> arr[i].first;
		arr[i].second = i;
		arr_rev[rv(i)] = arr[i];
	}

	vector<int> left = monotonic_stack(arr);
	vector<int> right = monotonic_stack(arr_rev);

	long long max_area = 0;

	for (int i = 0; i < n; i++) {
		int l = left[i], r = rv(right[rv(i)]);
		max_area = max(max_area, 1LL * arr[i].first * (r - l - 1));
	}

	cout << max_area << endl;

	return 0;
}
