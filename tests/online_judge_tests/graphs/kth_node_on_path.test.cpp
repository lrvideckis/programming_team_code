#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"
#include "../template.hpp"

#include "../../../library/graphs/lowest_common_ancestor.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<vector<pair<int, long long>>> adj(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].emplace_back(v, 1ll);
		adj[v].emplace_back(u, 1ll);
	}
	LCA lca(adj);
	while (q--) {
		int u, v, k;
		cin >> u >> v >> k;
		if (k > lca.dist_edges(u, v))
			cout << -1 << '\n';
		else
			cout << lca.kth_path(u, v, k) << '\n';
	}
}
