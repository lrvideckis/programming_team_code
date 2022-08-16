#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_A"
#include "../../template.h"

#include "../../../library/flow/dinic.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int v, e;
	cin >> v >> e;

	max_flow mf(v);

	while(e--) {
		int u, v, c;
		cin >> u >> v >> c;
		mf.add_edge(u, v, c);
	}

	cout << mf.get_flow(0, v - 1) << '\n';

	return 0;
}
