#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include "../template.hpp"

#include "../../../library/graphs/tree_lift/constructor.hpp"

#include "../../../library/graphs/lca_rmq/get_lca.hpp"
#include "../../../library/graphs/lca_rmq/in_subtree.hpp"

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

#include "../../../library/graphs/tree_lift/lca_lift.hpp"

    LCA lca(adj);
    for (int i = 0; i < n; i++) {
        assert(lca_lift(i, i) == i);
        assert(get_lca(lca, i, i) == i);
        assert(lca.in[lca.order[i]] == i && lca.order[lca.in[i]] == i);
    }
    while (q--) {
        int u, v;
        cin >> u >> v;
        int curr_lca = lca_lift(u, v);
        assert(curr_lca == get_lca(lca, u, v));
        assert((curr_lca == u) == in_subtree(lca, u, v));
        assert((curr_lca == v) == in_subtree(lca, v, u));
        cout << curr_lca << '\n';
    }
}
