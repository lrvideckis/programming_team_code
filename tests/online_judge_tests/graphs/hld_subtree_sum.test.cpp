#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
#include "../template.hpp"

#include "../../../library/graphs/heavy_light_decomposition.hpp"
#include "../../../library/range_data_structures/binary_indexed_tree.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<int> values(n);
	for (int i = 0; i < n; i++)
		cin >> values[i];
	vector<vector<int>> adj(n);
	vector<int> par(n);
	for (int i = 1; i < n; i++) {
		cin >> par[i];
		adj[i].push_back(par[i]);
		adj[par[i]].push_back(i);
	}
	HLD h(adj);
	vector<long long> init(n);
	for (int i = 0; i < n; i++)
		init[h.tree[i].time_in] = values[i];
	BIT<long long> ft(init);
	while (q--) {
		int type;
		cin >> type;
		if (type == 0) {
			int idx, add;
			cin >> idx >> add;
			ft.update(h.tree[idx].time_in, add);
		} else {
			int u;
			cin >> u;
			auto [l, r] = h.subtree(u);
			cout << ft.sum(l, r) << '\n';
		}
	}
	return 0;
}
