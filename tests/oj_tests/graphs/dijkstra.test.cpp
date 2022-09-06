#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_A"
#include "../../template.hpp"

#include "../../../library/graphs/dijkstra.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, s;
	cin >> n >> m >> s;
	vector<vector<pair<int, long long>>> adj(n);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].emplace_back(v, w);
	}
	vector<long long> len = dijkstra(adj, s);
	for (int i = 0; i < n; i++) {
		if (len[i] == INF) cout << "INF\n";
		else cout << len[i] << '\n';
	}
	return 0;
}
