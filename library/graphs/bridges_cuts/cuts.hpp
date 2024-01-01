/** @file */
#pragma once
/**
 * Info about cut/articulation nodes
 */
struct cut_info {
    int num_bccs; /**< number of bi-connected components */
    vector<bool> is_cut; /**< is_cut[node] = 1 iff cut node */
    vector<int> bcc_id; /**< bcc_id[edge id] = id of bcc (which are labeled 0, 1, ..., `num_bccs`-1) */
};
/**
 * @see https://cp-algorithms.com/graph/cutpoints.html
 *
 * @code{.cpp}
       vector<vector<array<int, 2>>> adj(n);
       for (int i = 0; i < m; i++) {
           int u, v;
           cin >> u >> v;
           u--, v--;
           adj[u].push_back({v, i});
           adj[v].push_back({u, i});
       }
       auto [num_bccs, is_cut, bcc_id] = cuts(adj, m);
 * @endcode
 * @param adj undirected graph; possibly with multiple edges; self edges not allowed
 * @param m number of edges
 * @returns info about cut nodes.
 * @time O(n + m)
 * @space this function allocates and returns a `cut_info` struct, which is O(n + m)
 */
cut_info cuts(const vector<vector<array<int, 2>>>& adj, int m) {
    int n = ssize(adj), timer = 1, num_bccs = 0;
    vector<int> tin(n), bcc_id(m, -1), st;
    vector<bool> is_cut(n);
    auto dfs = [&](auto&& self, int u, int p_id) -> int {
        int low = tin[u] = timer++, deg = 0;
        for (auto [v, e_id] : adj[u]) {
            assert(u != v);
            if (e_id == p_id) continue;
            if (!tin[v]) {
                int siz = ssize(st);
                st.push_back(e_id);
                int low_ch = self(self, v, e_id);
                if (low_ch >= tin[u]) {
                    is_cut[u] = 1;
                    for (int i = siz; i < ssize(st); i++)
                        bcc_id[st[i]] = num_bccs;
                    st.resize(siz);
                    num_bccs++;
                }
                low = min(low, low_ch);
                deg++;
            } else if (tin[v] < tin[u]) {
                st.push_back(e_id);
                low = min(low, tin[v]);
            }
        }
        if (p_id == -1) is_cut[u] = (deg > 1);
        return low;
    };
    for (int i = 0; i < n; i++)
        if (!tin[i]) dfs(dfs, i, -1);
    return {num_bccs, is_cut, bcc_id};
}
