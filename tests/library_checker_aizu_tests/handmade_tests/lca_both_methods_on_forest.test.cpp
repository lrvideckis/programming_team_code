#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/misc/random.hpp"
#include "../../../library/data_structures/uncommon_data_structures/dsu_restorable.hpp"

#include "../../../library/graphs/tree_lift/dist_edges.hpp"
#include "../../../library/graphs/tree_lift/kth_path.hpp"

#include "../../../library/graphs/lca_rmq/dist_edges.hpp"
#include "../../../library/graphs/lca_rmq/next_on_path.hpp"

int main() {
    for (int n = 1; n <= 100; n++) {
        vector<vector<int>> adj(n);
        dsu_restorable dsu(n);
        for (int i = 0; i < n - 2; i++) {
            int u = get_rand<int>(0, n - 1);
            int v = get_rand<int>(0, n - 1);
            if (u == v)
                continue;
            if (dsu.join(u, v)) {
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
        }
        tree_lift tl(adj);
        LCA lca(adj);
        for (int i = 0; i < 100; i++) {
            int u = get_rand<int>(0, n - 1);
            int v = get_rand<int>(0, n - 1);
            if (u == v || !dsu.same_set(u, v))
                continue;
            assert(get_lca(tl, u, v) == get_lca(lca, u, v));
            assert(dist_edges(tl, u, v) == dist_edges(lca, u, v));
            assert(kth_path(tl, u, v, 1) == next_on_path(lca, u, v));
            if (tl.d[u] > tl.d[v]) swap(u, v);
            assert((u == kth_par(tl, v, tl.d[v] - tl.d[u])) == in_subtree(lca, u, v));
        }
    }
    cout << "Hello World\n";
    return 0;
}
