#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"
#include "../template.hpp"

#include "../../../library/data_structures/sparse_table.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
#include "../../../library/graphs/tree_lift/kth_path.hpp"
#include "../../../library/graphs/tree_lift/dist_edges_lift.hpp"
#include "../../../library/graphs/lca_rmq/dist_edges_rmq.hpp"
#include "../../../library/graphs/lca_rmq/next_on_path.hpp"
    while (q--) {
        int u, v, k;
        cin >> u >> v >> k;
        int dist_in_edges = dist_edges_lift(u, v);
        if (k > dist_in_edges)
            cout << -1 << '\n';
        else
            cout << kth_path(u, v, k) << '\n';
        assert(dist_in_edges == dist_edges_rmq(u, v));
        if (u != v) {
            assert(kth_path(u, v, 0) == u);
            assert(kth_path(u, v, 1) == next_on_path(u, v));
            assert(kth_path(u, v, dist_in_edges - 1) == next_on_path(v, u));
            assert(kth_path(u, v, dist_in_edges) == v);
        }
    }
}
