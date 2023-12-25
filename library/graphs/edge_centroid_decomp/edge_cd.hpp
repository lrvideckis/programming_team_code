/** @file */
#pragma once
/**
 * @see https://codeforces.com/blog/entry/104997 https://codeforces.com/blog/entry/120446
 * @code{.cpp}
 *     // only handle paths with >=1 edge in each set
 *     // i.e. handle single-edge paths separately
 *     edge_cd(adj, [&](const vector<vector<int>>& cd_adj, int cent, int split) -> void {
 *         // subtrees of prefix [0, split) of cd_adj[cent] are the first edge set
 *         // subtrees of suffix [split, ssize(cd_adj[cent])) of cd_adj[cent] are the second edge set
 *     });
 * @endcode
 */
template <class F> struct edge_cd {
    vector<vector<int>> adj;
    F f;
    vector<int> sub_sz;
    /**
     * @param a_adj,a_f unrooted tree and callback
     * @time O(n * log1.5(n))
     * @space `adj` and `sub_sz` arrays take O(n); recursion stack for `dfs` is
     * O(log1.5 n); recursion stack for `find_cent` is O(n)
     */
    edge_cd(const vector<vector<int>>& a_adj, F a_f) : adj(a_adj), f(a_f), sub_sz(ssize(adj)) {
        dfs(0, ssize(adj));
    }
    int find_cent(int u, int p, int siz) {
        sub_sz[u] = 1;
        for (int v : adj[u])
            if (v != p) {
                int cent = find_cent(v, u, siz);
                if (cent != -1) return cent;
                sub_sz[u] += sub_sz[v];
            }
        if (p == -1) return u;
        return 2 * sub_sz[u] >= siz ? sub_sz[p] = siz - sub_sz[u], u : -1;
    }
    void dfs(int u, int siz) {
        if (siz <= 2) return;
        u = find_cent(u, -1, siz);
        int sum = 0;
        auto it = partition(begin(adj[u]), end(adj[u]), [&](int v) -> bool {
            bool ret = 3 * (sum + sub_sz[v]) <= 2 * (siz - 1);
            if (ret) sum += sub_sz[v];
            return ret;
        });
        f(adj, u, int(it - begin(adj[u])));
        vector<int> oth(it, end(adj[u]));
        adj[u].erase(it, end(adj[u]));
        dfs(u, sum + 1);
        swap(adj[u], oth);
        dfs(u, siz - sum);
    }
};
