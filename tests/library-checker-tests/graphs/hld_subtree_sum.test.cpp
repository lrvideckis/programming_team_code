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
	vector<int> par(n);
	for(int i = 1; i < n; i++) {
		cin >> par[i];
		adj[i].push_back(par[i]);
		adj[par[i]].push_back(i);
	}
	hld h(adj, 0);
	vector<long long> rupqInit(n);
	for(int i = 0; i < n; i++) rupqInit[h.timeIn[i]] = values[i];
	for(int i = n-1; i > 0; i--) {
		rupqInit[h.timeIn[par[i]]] += rupqInit[h.timeIn[i]];
	}
	vector<long long> init(n);
	for(int i = 0; i < n; i++) {
		init[h.timeIn[i]] = values[i];
	}
	fenwickTree<long long> ft(init);
	rangeUpdatesAndPointQueries<long long> rupq(rupqInit);
	while(q--) {
		int type;
		cin >> type;
		if(type == 0) {
			int idx, add;
			cin >> idx >> add;
			ft.update(h.timeIn[idx], add);
			for(auto [l,r] : h.path(0, idx)) {
				rupq.update(l, r, add);
			}
		} else {
			int u;
			cin >> u;
			auto [l,r] = h.subtree(u);
			long long res = ft.sum(l, r);
			assert(res == rupq.query(h.timeIn[u]));
			cout << res << endl;
		}
	}
	return 0;
}
