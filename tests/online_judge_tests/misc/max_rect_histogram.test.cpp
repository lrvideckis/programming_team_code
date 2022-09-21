#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_3_C"
#include "../template.hpp"

#include "../../../library/misc/monotonic_stack_related/max_rect_histogram.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	cout << max_rect_histogram(arr) << endl;
	return 0;
}
