#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include "../template.hpp"

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
	LCA lca(adj);
	for (int i = 0; i < n; i++) {
		int curr_lca = lca.lca(i, i);
		assert(curr_lca == i);
	}
	while (q--) {
		int u, v;
		cin >> u >> v;
		cout << lca.lca(u, v) << '\n';
	}
}
