#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
#include "../../template.h"

#include "../../../Library/graphs/hld.h"
#include "../../../Library/range_data_structures/fenwickTree.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<int> values(n);
	for(int i = 0; i < n; i++) {
		cin >> values[i];
	}
	vector<vector<int>> adj(n);
	for(int i = 1; i < n; i++) {
		int par;
		cin >> par;
		adj[i].push_back(par);
		adj[par].push_back(i);
	}
	hld h(adj, 0);
	vector<long long> init(n);
	for(int i = 0; i < n; i++) {
		init[h.timeIn[i]] = values[i];
	}
	fenwickTree<long long> ft(init);
	while(q--) {
		int type;
		cin >> type;
		if(type == 0) {
			int idx, add;
			cin >> idx >> add;
			ft.update(h.timeIn[idx], add);
		} else {
			int u;
			cin >> u;
			auto [l,r] = h.subtree(v);
			cout << ft.sum(l, r) << endl;
		}
	}
	return 0;
}
