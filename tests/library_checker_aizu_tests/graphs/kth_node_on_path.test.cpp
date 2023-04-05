#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"
#include "../template.hpp"

#include "../../../library/graphs/tree_lifting.hpp"
#include "../../../library/graphs/least_common_ancestor.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<vector<int>> adj(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	tree_lift lift(adj);
	LCA lca(adj);
	while (q--) {
		int u, v, k;
		cin >> u >> v >> k;
		int dist_in_edges = lift.dist_edges(u, v);
		if (k > dist_in_edges)
			cout << -1 << '\n';
		else
			cout << lift.kth_path(u, v, k) << '\n';
		assert(dist_in_edges == lca.dist_edges(u, v));
		if (u != v) {
			assert(lift.kth_path(u, v, 1) == lca.first_on_path(u, v));
			//assert(lift.kth_path(u, v, dist_in_edges - 1) == lca.first_on_path(v, u));
			assert(lift.kth_path(u, v, dist_in_edges) == v);
		}
	}
}
