#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include "../template.hpp"

#include "../../../library/data_structures/sparse_table.hpp"

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

#include "../../../library/graphs/lca_rmq/lca_rmq.hpp"
#include "../../../library/graphs/lca_rmq/in_subtree.hpp"

    for (int i = 0; i < n; i++) {
        assert(lca_lift(i, i) == i);
        assert(lca_rmq(i, i) == i);
        assert(lca.in[lca.order[i]] == i && lca.order[lca.in[i]] == i);
    }
    while (q--) {
        int u, v;
        cin >> u >> v;
        int curr_lca = lca_lift(u, v);
        assert(curr_lca == lca_rmq(u, v));
        assert((curr_lca == u) == in_subtree(u, v));
        assert((curr_lca == v) == in_subtree(v, u));
        cout << curr_lca << '\n';
    }
}
