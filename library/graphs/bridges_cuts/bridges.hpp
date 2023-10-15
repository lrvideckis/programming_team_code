/** @file */
#pragma once
/**
 * Info about bridge edges
 */
struct bridge_info {
    int num_2_edge_ccs; /**< number of components in bridge tree */
    vector<bool> is_bridge; /**< is_bridge[edge id] = 1 iff bridge edge */
    vector<int> two_edge_ccid; /**< two_edge_ccid[node] = id of 2 edge component (labeled 0, 1, ..., `num_2_edge_ccs`-1) */
};
/**
 * @see https://cp-algorithms.com/graph/bridge-searching.html
 *
 * @code{.cpp}
 *     vector<vector<array<int, 2>>> adj;
 *     for (int i = 0; i < m; i++) {
 *         int u, v;
 *         cin >> u >> v;
 *         u--, v--;
 *         adj[u].push_back({v, i});
 *         adj[v].push_back({u, i});
 *     }
 *     auto [num_2_edge_ccs, is_bridge, two_edge_ccid] = bridges(adj, m);
 * @endcode
 * @param adj undirected graph; possibly with multiple edges
 * @param m number of edges
 * @returns info about both bridge edges
 * @time O(n + m)
 * @space this function allocates and returns a `bridge_info` struct, which is O(n + m)
 */
bridge_info bridges(const vector<vector<array<int, 2>>>& adj, int m) {
    int n = int(ssize(adj)), timer = 1, num_2_edge_ccs = 0;
    vector<int> tin(n), two_edge_ccid(n), st;
    vector<bool> is_bridge(m);
    st.reserve(n);
    auto dfs = [&](auto&& self, int u, int p_id) -> int {
        int low = tin[u] = timer++;
        st.push_back(u);
        for (auto [v, e_id] : adj[u]) {
            if (e_id == p_id) continue;
            if (!tin[v])
                low = min(low, self(self, v, e_id));
            else if (tin[v] < tin[u])
                low = min(low, tin[v]);
        }
        if (tin[u] == low) {
            if (p_id != -1) is_bridge[p_id] = 1;
            while (1) {
                int node = st.back();
                st.pop_back();
                two_edge_ccid[node] = num_2_edge_ccs;
                if (node == u) break;
            }
            num_2_edge_ccs++;
        }
        return low;
    };
    for (int i = 0; i < n; i++)
        if (!tin[i])
            dfs(dfs, i, -1);
    return {num_2_edge_ccs, is_bridge, two_edge_ccid};
}
