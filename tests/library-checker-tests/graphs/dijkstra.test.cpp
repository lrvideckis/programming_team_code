#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"
#include "../../template.h"

#include "../../Library/graphs/dijkstra.h"

signed main() {
	cin.tie(0)->sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	int s, t;
	cin >> s >> t;
	vector<vector<pair<int,ll>>> adj(n);
	for(int i = 0; i < m; i++) {
		int u,v,w;
		cin >> u >> v >> w;
		adj[u].push_back({v,w});
	}
	dij info = dijkstra(adj, s);
	if(info.len[t] == INF) {
		cout << -1 << endl;
		return 0;
	}
	vector<int> path;
	for(int node = t; node != s; node = info.par[node]) {
		path.push_back(node);
	}
	path.push_back(s);
	cout << info.len[t] << " " << (int)path.size()-1 << endl;

	for(int i = (int)path.size()-2; i >= 0; i--) {
		cout << path[i+1] << " " << path[i] << endl;
	}

	return 0;
}
