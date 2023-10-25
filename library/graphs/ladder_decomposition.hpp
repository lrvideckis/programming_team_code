/** @file */
#pragma once
#include "../../kactl/content/graph/BinaryLifting.h"
struct ladder_decomp {
    int n;
    vector<vector<int>> ladder, tbl;
    vector<int> deapest_leaf, depth, par;
    ladder_decomp(const vector<vector<int>>& adj) : n(int(ssize(adj))), ladder(n), deapest_leaf(n), depth(n), par(n, -1) {
        iota(begin(deapest_leaf), end(deapest_leaf), 0);
        for (int i = 0; i < n; i++)
            if (par[i] == -1) {
                par[i] = i;
                dfs(adj, i);
                ladder[deapest_leaf[i]].resize(2 * depth[deapest_leaf[i]]);
            }
        for (int i = 0; i < n; i++) {
            for(int j = 0, u = i; j < ssize(ladder[i]); j++, u = par[u]) {//TODO: see if I can remove `u` variable
                ladder[i][j] = u;
            }
        }
        tbl = treeJump(par);
    }
    void dfs(const vector<vector<int>>& adj, int u) {
        for (auto v : adj[u])
            if (v != par[u]) {
                par[v] = u;
                depth[v] = 1 + depth[u];//TODO tree lift style
                dfs(adj, v);
                if(depth[deapest_leaf[v]] > depth[deapest_leaf[u]]) {
                    deapest_leaf[u] = deapest_leaf[v];
                }
            }
        for (auto v : adj[u])//TODO see if we can do this in a single loop above
            if (v != par[u]) {
                if (deapest_leaf[u] != deapest_leaf[v]) {
                    ladder[deapest_leaf[v]].resize(2 * (depth[deapest_leaf[v]] - depth[v]));//TODO: don't allocate more memory if the ladder goes past the root
                }
            }
    }
    inline int kth_par(int u, int k) const {
        assert(0 <= k && k <= depth[u]);//TODO: not allow k=0?
        if (k == 0) return u;//TODO not have this special case?
        int bit = __lg(k);
        u = tbl[bit][u], k -= (1 << bit);
        int leaf = deapest_leaf[u];
        return ladder[leaf][k + depth[leaf] - depth[u]];
    }
};
