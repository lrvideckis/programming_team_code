#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"
#include "../../template.hpp"

#include "../../../library/graphs/kth_node_on_path.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<vector<pair<int, long long>>> adj(n);
	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].emplace_back(v, 1ll);
		adj[v].emplace_back(u, 1ll);
	}
	kth_node_on_path kpath(adj, 0);
	while (q--) {
		int u, v, k;
		cin >> u >> v >> k;
		if (k > kpath.lca.dist_edges(u, v)) cout << -1 << '\n';
		else cout << kpath.query(u, v, k) << '\n';
	}
}
