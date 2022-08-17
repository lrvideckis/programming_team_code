#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_B"
#include "../../template.h"

#include "../../../library/flow/min_cost_max_flow.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int n, m, f;
	cin >> n >> m >> f;

	min_cost_max_flow mcmf(n);

	while(m--) {
		int u, v, cap, cost;
		cin >> u >> v >> cap >> cost;
		mcmf.add_edge(u, v, cap, cost);
	}

	cout << mcmf.get_flow(0, n - 1, f) << '\n';

	return 0;
}
