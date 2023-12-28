/** @file */
#pragma once
#include "edge_cd.hpp"
struct LCA {
    vector<int> d;
    vector<vector<int>> mn_d, to_cent;
    int cmp(int u, int v) {return d[u] < d[v] ? u : v;}
    //TODO: document it only works on un-rooted trees
    LCA(const vector<vector<int>>& adj) : d(ssize(adj)), mn_d(ssize(adj)), to_cent(ssize(adj)) {
        auto dfs_d = [&](auto&& self, int u, int p) -> void {
            for (int v : adj[u])
                if (v != p)
                    d[v] = 1 + d[u], self(self, v, u);
        };
        dfs_d(dfs_d, 0, -1);
        edge_cd(adj, [&](const vector<vector<int>>& cd_adj, int cent, int split) -> void {
            auto dfs = [&](auto&& self, int u, int p, int side) -> void {
                mn_d[u].push_back(cmp(mn_d[p].back(), u));
                to_cent[u].push_back(cent);
                for (int v : cd_adj[u])
                    if (v != p) self(self, v, u, side);
            };
            mn_d[cent].push_back(cent);
            to_cent[cent].push_back(cent);
            for (int i = 0; i < ssize(cd_adj[cent]); i++)
                dfs(dfs, cd_adj[cent][i], cent, i < split);
        });
    }
    int get_lca(int u, int v) {
        if (u == v) return u;
        for (int i = min(ssize(mn_d[u]), ssize(mn_d[v])) - 1;; i--)
            if (to_cent[u][i] == to_cent[v][i])
                return cmp(mn_d[u][i], mn_d[v][i]);
        assert(0);
    }
};
