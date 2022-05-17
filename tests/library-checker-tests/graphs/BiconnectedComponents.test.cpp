#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"
#include "../../template.h"

#include "../../../Library/graphs/bridges_and_cuts.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	vector<vector<pair<int,int>>> adj(n);
	for(int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].emplace_back(v, i);
		adj[v].emplace_back(u, i);
	}

	info res = bridge_and_cut(adj, m);

	for(int i = 0; i < n; i++) {
		//cut node if there exists a pair of adjacent edges belonging to different BCCs
		bool isCut = false;
		for(int j = 0; j < (int)adj[i].size(); j++) {
			if(res.bccID[adj[i][0].second] != res.bccID[adj[i][j].second]) {
				isCut = true;
			}
		}
		assert(isCut == res.isCut[i]);
	}

	cout << res.numBCCs << endl;
	vector<vector<int>> ccs(res.numBCCs);
	for(int i = 0; i < m; i++) {
		ccs[res.bccID[i]].push_back(i);
	}
	for(auto& cc : ccs) {
		cout << cc.size() << " ";
		for(int node : cc) cout << node << " ";
		cout << endl;
	}

	return 0;
}
