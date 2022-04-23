#define PROBLEM "https://judge.yosupo.jp/problem/assignment"
#include "../../template.h"

#include "../../content/maxflow/hungarian.h"

int main() {
	cin.tie(0)->sync_with_stdio(false);
	int n;
	cin >> n;
	vector<vector<ll>> a(n+1, vector<ll>(n+1));
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cin >> a[i][j];
		}
	}
	match res = HungarianMatch(a);
	cout << res.cost << endl;
	for(int i = 1; i <= n; i++) {
		cout << res.matching[i]-1 << " ";
	}
	return 0;
}
