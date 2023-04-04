#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"
#include "../template.hpp"

#include "../../../library/graphs/tree_lifting.hpp"

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
	while (q--) {
		int u, v, k;
		cin >> u >> v >> k;
		if (k > lift.dist_edges(u, v))
			cout << -1 << '\n';
		else
			cout << lift.kth_path(u, v, k) << '\n';
	}
}
