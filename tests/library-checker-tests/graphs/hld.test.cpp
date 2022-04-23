#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include "../../stress-tests/test_utilities/template.h"

#include "../../../Library/graphs/hld.h"

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,q;
	cin >> n >> q;
	vector<vector<int>> adj(n);
	for(int i = 1; i < n; ++i) {
		int par;
		cin >> par;
		adj[par].push_back(i);
		adj[i].push_back(par);
	}
	hld h(adj,0);
	while(q--) {
		int u,v;
		cin >> u >> v;
		cout << h.lca(u,v) << endl;
	}
}
