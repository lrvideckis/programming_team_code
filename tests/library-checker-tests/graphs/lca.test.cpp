#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include "../../template.h"

#include "../../../Library/graphs/lca.h"
#include "../../../Library/graphs/hld.h"

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,q;
	cin >> n >> q;
	vector<vector<pair<int,long long>>> adj(n);
	vector<int> depth(n, 0);
	for(int i = 1; i < n; ++i) {
		int par;
		cin >> par;
		depth[i] = 1 + depth[par];
		adj[par].push_back({i,1LL});
		adj[i].push_back({par,1LL});
	}

	for(int i = 0; i < n; ++i) {
		assert(0 == h.kthPar(i, depth[i]));
		assert(0 == h.kthPar(i, 1e9));
	}

	lca h(adj, 0);
	hld h2(adj, 0);
	while(q--) {
		int u, v;
		cin >> u >> v;
		int res = h.getLca(u,v);
		assert(h2.getLca(u,v) == res);
		assert(res == h.kthPar(u, depth[u] - depth[res]));
		assert(res == h.kthPar(v, depth[v] - depth[res]));
		cout << res << endl;
	}
}
