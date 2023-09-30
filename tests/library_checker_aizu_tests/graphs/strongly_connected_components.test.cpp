#define PROBLEM "https://judge.yosupo.jp/problem/scc"
#include "../template.hpp"

#include "../../../library/graphs/strongly_connected_components/add_edges_strongly_connected.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    auto [num_sccs, scc_id] = get_sccs(adj);
    {
        vector<bool> is_zero_in(num_sccs, 1), is_zero_out(num_sccs, 1);
        for (int i = 0; i < n; i++) {
            for (int v : adj[i]) {
                if (scc_id[i] == scc_id[v]) continue;
                is_zero_in[scc_id[v]] = 0;
                is_zero_out[scc_id[i]] = 0;
            }
        }
        // since {num_sccs-1, ..., 2, 1, 0} is a topo order
        assert(is_zero_in[num_sccs - 1] && is_zero_out[0]);
        int num_zero_in = int(count(begin(is_zero_in), end(is_zero_in), 1));
        int num_zero_out = int(count(begin(is_zero_out), end(is_zero_out), 1));
        vector<pair<int, int>> extra_edge_list = extra_edges(adj, num_sccs, scc_id);
        if (num_sccs == 1) assert(ssize(extra_edge_list) == 0);
        else assert(ssize(extra_edge_list) == max(num_zero_in, num_zero_out));
        vector<vector<int>> adj_copy(adj);
        for (auto [u, v] : extra_edge_list) {
            assert(u != v);
            adj_copy[u].push_back(v);
        }
        assert(get_sccs(adj_copy).num_sccs == 1);
    }
    //sanity check for reverse topo order of SCCs
    for (int i = 0; i < n; i++) {
        for (auto j : adj[i])
            assert(scc_id[i] >= scc_id[j]);
    }
    cout << num_sccs << '\n';
    vector<vector<int>> each_scc(num_sccs);
    for (int i = 0; i < n; i++)
        each_scc[scc_id[i]].push_back(i);
    for (int i = num_sccs - 1; i >= 0; i--) {
        cout << each_scc[i].size() << " ";
        for (auto node : each_scc[i])
            cout << node << " ";
        cout << '\n';
    }
    return 0;
}
