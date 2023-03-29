#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include "../template.hpp"

#include "../../../library/graphs/tree_lifting.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<vector<int>> adj(n);
	for(int i = 1; i < n; i++) {
		int par;
		cin >> par;
		adj[i].push_back(par);
		adj[par].push_back(i);
	}
	tree_lift lift(adj);
	while(q--) {
		int u, v;
		cin >> u >> v;
		cout << lift.lca(u, v) << '\n';
	}
}
