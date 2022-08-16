#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_B"
#include "../../template.h"

#include "../../../library/flow/min_cost_max_flow.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int v, e, f;
	cin >> v >> e >> f;

	min_cost_max_flow mcmf(v);

	while(e--) {
		int u, v, cap, cost;
		cin >> u >> v >> cap >> cost;
		mcmf.add_edge(u, v, cap, cost);
	}

	cout << mcmf.get_flow(0, v - 1, f) << '\n';

	return 0;
}
