#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"
#include "../template.hpp"

#include "../../../library/graphs/lca_rmq/lca_rmq.hpp"
#include "../../../library/graphs/ladder_decomposition.hpp"

//TODO test forest
//TODO test directed tree (edges point to children)
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
    LCA lca(adj);
    ladder_decomp ld(adj);
    while (q--) {
        int u, v, k;
        cin >> u >> v >> k;
        int lca_d = lca.d[lca.get_lca(u, v)];
        int u_lca = lca.d[u] - lca_d;
        int v_lca = lca.d[v] - lca_d;
        if(k > u_lca + v_lca) cout << -1 << '\n';
        else cout << (k <= u_lca ? ld.kth_par(u, k) : ld.kth_par(v, u_lca + v_lca - k)) << '\n';
    }
}
