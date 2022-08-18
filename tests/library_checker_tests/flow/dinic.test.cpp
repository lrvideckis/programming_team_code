#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_A"
#include "../../template.h"

#include "../../../library/flow/dinic.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	max_flow mf(n);
	while (m--) {
		int u, v, c;
		cin >> u >> v >> c;
		mf.add_edge(u, v, c);
	}
	cout << mf.get_flow(0, n - 1) << '\n';
	return 0;
}
