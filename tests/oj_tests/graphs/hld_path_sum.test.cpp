#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"
#include "../../template.hpp"
#include "../../random.hpp"

#include "../../../library/graphs/hld.hpp"
#include "../../../library/range_data_structures/bit.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<int> values(n);
	for (int i = 0; i < n; i++)
		cin >> values[i];
	vector<vector<int>> adj(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	HLD h(adj, get_rand<int>(0, n)/*random root*/);
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
			int u, v;
			cin >> u >> v;
			long long res = 0;
			for (auto [l, r] : h.path(u, v))
				res += ft.sum(l, r);
			cout << res << endl;
		}
	}
	return 0;
}
