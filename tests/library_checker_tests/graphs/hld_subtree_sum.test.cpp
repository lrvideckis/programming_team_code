#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
#include "../../template.h"

#include "../../../library/graphs/hld.h"
#include "../../../library/range_data_structures/bit.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<int> values(n);
	for(int i = 0; i < n; i++) {
		cin >> values[i];
	}
	vector<vector<int>> adj(n);
	vector<int> par(n);
	for(int i = 1; i < n; i++) {
		cin >> par[i];
		adj[i].push_back(par[i]);
		adj[par[i]].push_back(i);
	}
	HLD h(adj, 0);
	vector<long long> init(n);
	for(int i = 0; i < n; i++) {
		init[h.time_in[i]] = values[i];
	}
	BIT<long long> ft(init);
	while(q--) {
		int type;
		cin >> type;
		if(type == 0) {
			int idx, add;
			cin >> idx >> add;
			ft.update(h.time_in[idx], add);
		} else {
			int u;
			cin >> u;
			auto [l, r] = h.subtree(u);
			cout << ft.sum(l, r) << endl;
		}
	}
	return 0;
}
