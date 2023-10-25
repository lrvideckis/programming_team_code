#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"
#include "../template.hpp"
#include "../../../library/graphs/bridges_cuts/bridge_tree.hpp"
#include "../../../library/data_structures/uncommon_data_structures/dsu_restorable.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m;
    cin >> n >> m;
    vector<vector<array<int, 2>>> adj(n);
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        edges[i] = {u, v};
    }
    bridge_info cc = bridges(adj, m);
    vector<vector<int>> bt = bridge_tree(adj, cc);
    //check correctness of bridge tree
    {
        assert(ssize(bt) == cc.num_2_edge_ccs);
        for (int v = 0; v < cc.num_2_edge_ccs; v++) {
            for (auto to : bt[v])
                assert(to != v); //didn't add any non-bridge
        }
        int sum_deg = accumulate(begin(bt), end(bt), 0, [](int sum, const auto & neighbors) -> int {
            return sum + int(ssize(neighbors));
        });
        int cnt_bridges = accumulate(begin(cc.is_bridge), end(cc.is_bridge), 0);
        assert(sum_deg % 2 == 0 && sum_deg / 2 == cnt_bridges);
    }
    dsu_restorable dsu(n);
    int num_sets_dsu = n;
    for (int i = 0; i < m; i++) {
        if (!cc.is_bridge[i]) {
            auto [u, v] = edges[i];
            num_sets_dsu -= dsu.join(u, v);
        }
    }
    assert(num_sets_dsu == ssize(bt));
    for (int i = 0; i < m; i++) {
        if (cc.is_bridge[i]) {
            auto [u, v] = edges[i];
            bool same_set = dsu.same_set(u, v);
            assert(!same_set);
        }
    }
    for (int i = 0; i < n; i++) {
        int par_of_cc = dsu.find(i);
        assert(cc.two_edge_ccid[i] == cc.two_edge_ccid[par_of_cc]);
    }
    for (int i = 0; i < m; i++) {
        auto [u, v] = edges[i];
        //bridge if nodes are from different 2-edge CCs
        assert(cc.is_bridge[i] == (cc.two_edge_ccid[u] != cc.two_edge_ccid[v]));
    }
    vector<vector<int>> ccs(cc.num_2_edge_ccs);
    for (int i = 0; i < n; i++)
        ccs[cc.two_edge_ccid[i]].push_back(i);
    cout << cc.num_2_edge_ccs << '\n';
    for (const auto& curr_cc : ccs) {
        cout << ssize(curr_cc) << " ";
        for (auto node : curr_cc)
            cout << node << " ";
        cout << '\n';
    }
    return 0;
}
