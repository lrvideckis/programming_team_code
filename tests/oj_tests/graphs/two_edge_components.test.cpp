#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"
#include "../../../kactl/stress-tests/utilities/template.h"

#include "../../../kactl/content/data-structures/UnionFind.h"
#include "../../../library/graphs/bridge_tree.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	vector<vector<pair<int, int>>> adj(n);
	vector<pair<int, int>> edges(m);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].emplace_back(v, i);
		adj[v].emplace_back(u, i);
		edges[i] = {u, v};
	}
	info cc = bridge_and_cut(adj, m);
	vector<vector<int>> bt = bridge_tree(adj, cc);
	//check correctness of bridge tree
	{
		assert((int)bt.size() == cc.num_2_edge_ccs);
		set<pair<int, int>> seen_edges;
		int sum_deg = 0;
		for (int v = 0; v < cc.num_2_edge_ccs; v++) {
			sum_deg += bt[v].size();
			for (int to : bt[v]) {
				assert(to != v); //didn't add any non-bridge
				assert(!seen_edges.count({v, to}));//didn't add a bridge twice
				seen_edges.insert({v, to});
			}
		}
		for (auto [u, v] : seen_edges) {
			assert(seen_edges.count({v, u}));
		}
		int cnt_bridges = 0;
		for (int i = 0; i < m; i++)
			cnt_bridges += cc.is_bridge[i];
		assert(sum_deg % 2 == 0 && sum_deg / 2 == cnt_bridges);
		assert(seen_edges.size() % 2 == 0 && (int)seen_edges.size() / 2 == cnt_bridges);
		for (int v = 0; v < cc.num_2_edge_ccs; v++)
			sort(bt[v].begin(), bt[v].end());
		for (int i = 0; i < m; i++) {
			auto [u, v] = edges[i];
			u = cc.two_edge_ccid[u];
			v = cc.two_edge_ccid[v];
			for (int j = 0; j < 2; j++) {
				auto it = lower_bound(bt[u].begin(), bt[u].end(), v);
				bool in_adj_list = (it != bt[u].end() && (*it) == v);
				assert(in_adj_list == cc.is_bridge[i]);
				swap(u, v);
			}
		}
	}
	UF dsu(n);
	for (int i = 0; i < m; i++) {
		if (!cc.is_bridge[i]) {
			auto [u, v] = edges[i];
			dsu.join(u, v);
		}
	}
	for (int i = 0; i < m; i++) {
		if (cc.is_bridge[i]) {
			auto [u, v] = edges[i];
			assert(dsu.find(u) != dsu.find(v));
		}
	}
	for (int i = 0; i < n; i++)
		assert(cc.two_edge_ccid[i] == cc.two_edge_ccid[dsu.find(i)]);
	for (int i = 0; i < m; i++) {
		auto [u, v] = edges[i];
		//bridge if nodes are from different 2-edge CCs
		assert(cc.is_bridge[i] == (cc.two_edge_ccid[u] != cc.two_edge_ccid[v]));
	}
	vector<vector<int>> ccs(cc.num_2_edge_ccs);
	for (int i = 0; i < n; i++)
		ccs[cc.two_edge_ccid[i]].push_back(i);
	cout << cc.num_2_edge_ccs << endl;
	for (auto& curr_cc : ccs) {
		cout << curr_cc.size() << " ";
		for (int node : curr_cc) cout << node << " ";
		cout << endl;
	}
	return 0;
}
