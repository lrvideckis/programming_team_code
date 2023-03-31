#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/misc/random.hpp"

#include "../../../library/data_structures/dsu_restorable.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	for (int n = 1; n < 100; n++) {
		dsu_restorable dsu(n);
		vector<vector<int>> adj(n);
		for (int q = 0; q < 100; q++) {
			if (get_rand<int>(0, 2) == 0) {
				int u = get_rand<int>(0, n), v = get_rand(0, n);
				dsu.update(u, v);
				adj[u].push_back(v);
				adj[v].push_back(u);
			} else {
				int u = get_rand<int>(0, n);
				vector<bool> vis(n);
				int size_component = 0;
				auto dfs = [&](auto&& self, int node) -> void {
					size_component++;
					for (int next : adj[node])
						if (!vis[next]) {
							vis[next] = true;
							self(self, next);
						}
				};
				vis[u] = true;
				dfs(dfs, u);
				assert(size_component == dsu.size(u));
			}
		}
	}
	cout << "Hello World\n";
	return 0;
}
