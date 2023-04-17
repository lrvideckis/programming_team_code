/** @file */
#pragma once
/**
 * @author camc
 * @code{.cpp}
 *     //example usage
 *     centroid_decomp(adj, [&](const vector<vector<int>>& adj_removed_edges, int cent) -> void {
 *     });
 * @endcode
 */
template <typename F> struct centroid_decomp {
    vector<vector<int>> adj; /**< copy of tree where we remove edges to represent each decomposition */
    F func; /**< copy of function */
    vector<int> sub_sz; /**< subtree sizes of current decomponsition */
    /**
     * @param a_adj unweighted undirected forest
     * @param a_func called on centroid of each decomposition
     * @time O(n log n) each node is adjacent to O(logn) centroids
     * @memory O(n)
     */
    centroid_decomp(const vector<vector<int>>& a_adj, const F& a_func)
        : adj(a_adj), func(a_func), sub_sz(ssize(adj), -1) {
        for (int i = 0; i < ssize(adj); i++)
            if (sub_sz[i] == -1)
                dfs(i);
    }
    void calc_subtree_sizes(int u, int p = -1) {
        sub_sz[u] = 1;
        for (auto v : adj[u]) {
            if (v == p) continue;
            calc_subtree_sizes(v, u);
            sub_sz[u] += sub_sz[v];
        }
    }
    void dfs(int u) {
        calc_subtree_sizes(u);
        for (int p = -1, sz_root = sub_sz[u];;) {
            auto big_ch = find_if(adj[u].begin(), adj[u].end(), [&](int v) -> bool {
                return v != p && 2 * sub_sz[v] > sz_root;
            });
            if (big_ch == adj[u].end()) break;
            p = u, u = *big_ch;
        }
        func(adj, u);
        for (auto v : adj[u]) {
            adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
            dfs(v);
        }
    }
};
