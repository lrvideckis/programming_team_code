#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include "../template.hpp"

#include "../../../library/graphs/lca.hpp"
#include "../../../library/graphs/hld.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<vector<int>> adj(n);
	vector<vector<pair<int, long long>>> adj_weighted(n);
	vector<int> depth(n, 0);
	for (int i = 1; i < n; i++) {
		int par;
		cin >> par;
		depth[i] = 1 + depth[par];
		adj_weighted[par].push_back({i, 1LL});
		adj_weighted[i].push_back({par, 1LL});
		adj[par].push_back(i);
		adj[i].push_back(par);
	}
	LCA h(adj_weighted);
	HLD h2(adj);
	for (int i = 0; i < n; i++) {
		assert(0 == h.kth_par(i, depth[i]));
		assert(0 == h.kth_par(i, 1e9));
	}
	while (q--) {
		int u, v;
		cin >> u >> v;
		int res = h.get_lca(u, v);
		assert(h2.lca(u, v) == res);
		assert(res == h.kth_par(u, depth[u] - depth[res]));
		assert(res == h.kth_par(v, depth[v] - depth[res]));
		cout << res << endl;
	}
}
