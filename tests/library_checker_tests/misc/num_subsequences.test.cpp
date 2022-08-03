#define PROBLEM "https://judge.yosupo.jp/problem/number_of_subsequences"
#include "../../template.h"

#include "../../../library/misc/num_distinct_subsequences.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);

	const int mod = 998244353;

	int n;
	cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	cout << (num_subsequences(arr, mod) - 1 + mod) % mod << endl;
	return 0;
}
