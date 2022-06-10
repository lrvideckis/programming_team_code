#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"
#include "../../template.h"

#include "../../../library/graphs/bridges_and_cuts.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	vector<vector<pair<int,int>>> adj(n);
	vector<pair<int,int>> edges(m);
	for(int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].emplace_back(v, i);
		adj[v].emplace_back(u, i);
		edges[i] = {u, v};
	}

	info res = bridge_and_cut(adj, m);

	for(int i = 0; i < m; i++) {
		auto [u, v] = edges[i];
		//bridge if nodes are from different 2-edge CCs
		assert(res.is_bridge[i] == (res.two_edge_ccid[u] != res.two_edge_ccid[v]));
	}

	vector<vector<int>> ccs(res.num_2_edge_ccs);
	for(int i = 0; i < n; i++) {
		ccs[res.two_edge_ccid[i]].push_back(i);
	}
	cout << res.num_2_edge_ccs << endl;
	for(auto& cc : ccs) {
		cout << cc.size() << " ";
		for(int node : cc) cout << node << " ";
		cout << endl;
	}

	return 0;
}
