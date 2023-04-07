#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/misc/random.hpp"
#include "../../../library/data_structures/dsu_restorable.hpp"
#include "../../../library/graphs/tree_lifting.hpp"
#include "../../../library/graphs/least_common_ancestor.hpp"

int main() {
	for (int n = 1; n <= 100; n++) {
		vector<vector<int>> adj(n);
		dsu_restorable dsu(n);
		for (int i = 0; i < n - 2; i++) {
			int u = get_rand<int>(0, n);
			int v = get_rand<int>(0, n);
			if (u == v)
				continue;
			if (dsu.update(u, v)) {
				adj[u].push_back(v);
				adj[v].push_back(u);
			}
		}
		tree_lift tl(adj);
		LCA lca(adj);
		for (int i = 0; i < 100; i++) {
			int u = get_rand<int>(0, n);
			int v = get_rand<int>(0, n);
			if (u == v || !dsu.same_set(u, v))
				continue;
			assert(tl.lca(u, v) == lca.lca(u, v));
			assert(tl.dist_edges(u, v) == lca.dist_edges(u, v));
			assert(tl.kth_path(u, v, 1) == lca.next_on_path(u, v));
			if (tl.d[u] > tl.d[v]) swap(u, v);
			assert((u == tl.kth(v, tl.d[v] - tl.d[u])) == lca.in_subtree(u, v));
		}
	}
	cout << "Hello World\n";
	return 0;
}
