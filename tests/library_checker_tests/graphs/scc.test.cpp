#define PROBLEM "https://judge.yosupo.jp/problem/scc"
#include "../../template.h"

#include "../../../library/graphs/scc.h"

int main() {
	cin.tie(0)->sync_with_stdio(false);
	int n,m;
	cin >> n >> m;
	vector<vector<int>> adj(n);
	for(int i = 0; i < m; i++) {
		int u,v;
		cin >> u >> v;
		adj[u].push_back(v);
	}
	scc_info info = SCC(adj);

	//sanity check for reverse topo order of SCCs
	for (int i = 0; i < n; i++) {
		for (int j : adj[i]) {
			assert(info.scc_id[i] >= info.scc_id[j]);
		}
	}

	cout << info.num_sccs << endl;
	vector<vector<int>> eachScc(info.num_sccs);
	for(int i = 0; i < n; i++) {
		eachScc[info.scc_id[i]].push_back(i);
	}
	for(int i = info.num_sccs - 1; i >= 0; i--) {
		cout << eachScc[i].size() << " ";
		for(int node : eachScc[i]) cout << node << " ";
		cout << endl;
	}
	return 0;
}
