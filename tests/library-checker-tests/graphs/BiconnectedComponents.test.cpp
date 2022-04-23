#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"
#include "../../template.h"

#include "../../../Library/graphs/bridges_and_cuts.h"

int main() {
	cin.tie(0)->sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> adj(n);
	vector<pair<int,int>> edges;
	for(int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
		edges.push_back({u,v});
	}

	biconnected_components bcc(adj);
	block_cut_tree bct(bcc);

	map<int,vector<int>> res;

	for(int i = 0; i < m; i++) {
		auto [u,v] = edges[i];
		int idx = bct.which_bcc(u,v);
		if(idx != -1) {
			res[idx].push_back(i);
		}
	}

	cout << res.size() << endl;
	for(auto &[id, currBcc] : res) {
		cout << currBcc.size() << " ";
		for(int idx : currBcc) {
			cout << idx << " ";
		}
		cout << endl;
	}

	return 0;
}
