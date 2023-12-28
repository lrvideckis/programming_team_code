#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include "../template.hpp"

#include "../../../library/graphs/edge_centroid_decomp/lca.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int par;
        cin >> par;
        adj[par].push_back(i);
        adj[i].push_back(par);
    }
    LCA lca(adj);
    for (int i = 0; i < n; i++) {
        int curr_1 = lca.get_lca(i, i);
        assert(curr_1 == i);
        int curr_2 = lca.get_lca(i, i);
        assert(curr_2 == i);
    }
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca.get_lca(u, v) << '\n';
    }
}
