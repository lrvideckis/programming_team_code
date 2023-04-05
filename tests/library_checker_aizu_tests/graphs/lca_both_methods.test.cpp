#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include "../template.hpp"

#include "../../../library/graphs/tree_lifting.hpp"
#include "../../../library/graphs/least_common_ancestor.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<vector<int>> adj(n);
	for (int i = 1; i < n; i++) {
		int par;
		cin >> par;
		adj[par].push_back(i);
	}
	tree_lift lift(adj);
	LCA lca(adj);
	for (int i = 0; i < n; i++) {
		assert(lift.lca(i, i) == i);
		assert(lca.lca(i, i) == i);
	}
	while (q--) {
		int u, v;
		cin >> u >> v;
		int curr_lca = lift.lca(u, v);
		assert(curr_lca == lca.lca(u, v));
		assert((curr_lca == u) == lca.in_subtree(u, v));
		assert((curr_lca == v) == lca.in_subtree(v, u));
		cout << curr_lca << '\n';
	}
}
