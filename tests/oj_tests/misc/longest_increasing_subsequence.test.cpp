#define PROBLEM "https://judge.yosupo.jp/problem/longest_increasing_subsequence"
#include "../../template.hpp"

#include "../../../library/misc/lis.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	vector<int> lis = LIS<int>(arr);
	cout << lis.size() << endl;
	for (int idx : lis) cout << idx << " ";
	cout << endl;
	return 0;
}
