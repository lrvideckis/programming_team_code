#define PROBLEM "https://judge.yosupo.jp/problem/tree_diameter"
#include "../../template.hpp"

#include "../../../library/graphs/kth_node_on_path.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	vector<vector<pair<int, long long>>> adj(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].emplace_back(v, w);
		adj[v].emplace_back(u, w);
	}
	kth_node_on_path kpath(adj);
	int u = 0;
	for (int i = 1; i < n; i++)
		if (kpath.lca.dist_weight(0, i) > kpath.lca.dist_weight(0, u)) u = i;
	int v = 0;
	for (int i = 1; i < n; i++)
		if (kpath.lca.dist_weight(u, i) > kpath.lca.dist_weight(u, v)) v = i;
	int len_diam = kpath.lca.dist_edges(u, v) + 1;
	cout << kpath.lca.dist_weight(u, v) << " " << len_diam << endl;
	for (int i = 0; i < len_diam; i++)
		cout << kpath.query(u, v, i) << " ";
	cout << endl;
}
