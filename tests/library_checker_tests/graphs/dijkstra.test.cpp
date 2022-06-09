#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"
#include "../../template.h"

#include "../../../library/graphs/dijkstra.h"

int main() {
	cin.tie(0)->sync_with_stdio(false);

	int n, m;
	cin >> n >> m;
	int s, t;
	cin >> s >> t;
	vector<vector<pair<int,long long>>> adj(n), inv(n);
	for(int i = 0; i < m; i++) {
		int u,v,w;
		cin >> u >> v >> w;
		adj[u].push_back({v,w});
		inv[v].push_back({u,w});
	}
	vector<long long> len = dijkstra(adj, s);
	if(len[t] == INF) {
		cout << -1 << endl;
		return 0;
	}

	vector<int> par(n, -1);
	auto dfs = [&](auto&& dfs, int node) -> void {
		for(auto [prev, weight] : inv[node]) {
			if(par[prev] == -1 && len[prev] + weight == len[node]) {
				par[prev] = node;
				dfs(dfs, prev);
			}
		}
	};

	dfs(dfs, t);

	vector<int> path;
	for(int node = s; node != t; node = par[node]) {
		path.push_back(node);
	}
	path.push_back(t);

	cout << len[t] << " " << (int)path.size()-1 << endl;

	for(int i = 0; i+1 < (int)path.size(); i++) {
		cout << path[i] << " " << path[i+1] << endl;
	}

	return 0;
}
