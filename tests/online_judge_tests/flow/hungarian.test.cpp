#define PROBLEM "https://judge.yosupo.jp/problem/assignment"
#include "../template.hpp"

#include "../../../library/flow/hungarian.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	vector<vector<long long>> a(n + 1, vector<long long>(n + 1));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			cin >> a[i][j];
	}
	weighted_match res = hungarian(a);
	cout << res.min_weight << '\n';
	for (int i = 1; i <= n; i++)
		cout << res.l_to_r[i] - 1 << " ";
	return 0;
}
