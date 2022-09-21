#define PROBLEM "https://judge.yosupo.jp/problem/number_of_subsequences"
#include "../template.hpp"

#include "../../../library/misc/num_distinct_subsequences.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	const int MOD = 998244353;
	int n;
	cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	cout << (num_subsequences(arr, MOD) - 1 + MOD) % MOD << endl;
	return 0;
}
