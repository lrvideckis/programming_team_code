#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection"
#include "../template.hpp"

#include "../../../library/graphs/strongly_connected_components/add_edges_strongly_connected.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<vector<pair<int, int>>> adj_edge_id(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj_edge_id[u].emplace_back(v, i);
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
        vector<array<int, 2>> edges = extra_edges(adj, num_sccs, scc_id);
        if (num_sccs == 1) assert(ssize(edges) == 0);
        else assert(ssize(edges) == max(num_zero_in, num_zero_out));
        vector<vector<int>> adj_copy(adj);
        for (auto [u, v] : edges) {
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
    vector<int> color(n);
    vector<pair<int/*edge id*/, int/*node closer to root*/>> edge_stack;
    auto dfs = [&](auto&& self, int u) -> void {
        for (auto [v, e_id] : adj_edge_id[u]) {
            if (color[v] == 0) {
                color[v] = 1;
                edge_stack.emplace_back(e_id, u);
                self(self, v);
                edge_stack.pop_back();
                color[v] = 2;
            } else if (color[v] == 1) {
                vector<int> res(1, e_id);
                while (1) {
                    auto [curr_edge_id, curr_node] = edge_stack.back();
                    edge_stack.pop_back();
                    res.push_back(curr_edge_id);
                    if (curr_node == v) break;
                }
                cout << ssize(res) << '\n';
                for (int i = ssize(res) - 1; i >= 0; i--)
                    cout << res[i] << '\n';
                exit(0);
            }
        }
    };
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            color[i] = 1;
            dfs(dfs, i);
            color[i] = 2;
        }
    }
    assert(num_sccs == n);
    cout << -1 << '\n';
    return 0;
}
