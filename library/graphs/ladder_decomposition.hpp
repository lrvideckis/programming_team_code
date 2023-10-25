/** @file */
#pragma once
#include "../../kactl/content/graph/BinaryLifting.h"
struct ladder_decomp {
    int n;
    vector<vector<int>> ladder, tbl;
    vector<int> deap/*deapest leaf*/, d, p;
    ladder_decomp(const vector<vector<int>>& adj) : n(int(ssize(adj))), ladder(n), deap(n), d(n), p(n, -1) {
        iota(begin(deap), end(deap), 0);
        for (int i = 0; i < n; i++)
            if (p[i] == -1)
                p[i] = i, dfs(adj, i);
        for (int i = 0; i < n; i++)
            if (p[i] == i || deap[p[i]] != deap[i]) {
                int leaf = deap[i], len = min(2 * (d[leaf] - d[i]), d[leaf]) + 1;
                ladder[leaf].resize(len, leaf);
                for (int j = 1; j < len; j++)
                    ladder[leaf][j] = p[ladder[leaf][j - 1]];
            }
        tbl = treeJump(p);
    }
    void dfs(const vector<vector<int>>& adj, int u) {
        for (auto v : adj[u])
            if (v != p[u]) {
                d[v] = d[p[v] = u] + 1;
                dfs(adj, v);
                if (d[deap[v]] > d[deap[u]])
                    deap[u] = deap[v];
            }
    }
    inline int kth_par(int u, int k) const {
        assert(0 <= k && k <= d[u]);
        if (k == 0) return u;
        int bit = __lg(k);
        u = tbl[bit][u], k -= (1 << bit);
        int leaf = deap[u];
        return ladder[leaf][k + d[leaf] - d[u]];
    }
};
