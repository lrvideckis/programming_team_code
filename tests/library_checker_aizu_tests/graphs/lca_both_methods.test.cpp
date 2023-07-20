#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include "../template.hpp"

#include "../../../library/graphs/tree_lift/get_lca.hpp"

#include "../../../library/graphs/lca_rmq/get_lca.hpp"
#include "../../../library/graphs/lca_rmq/next_on_path.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int par;
        cin >> par;
        adj[par].push_back(i);
    }
    tree_lift tl(adj);
    LCA lca(adj);
    for (int i = 0; i < n; i++) {
        assert(get_lca(tl, i, i) == i);
        assert(lca.get_lca(i, i) == i);
        assert(lca.in[lca.order[i]] == i && lca.order[lca.in[i]] == i);
    }
    while (q--) {
        int u, v;
        cin >> u >> v;
        int curr_lca = get_lca(tl, u, v);
        assert(curr_lca == lca.get_lca(u, v));
        assert((curr_lca == u) == in_subtree(lca, u, v));
        assert((curr_lca == v) == in_subtree(lca, v, u));
        cout << curr_lca << '\n';
    }
}
