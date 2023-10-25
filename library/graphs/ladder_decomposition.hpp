/** @file */
#pragma once
#include "../../kactl/content/graph/BinaryLifting.h"
struct ladder {
    int n;
    vector<vector<int>> b_tbl, l_tbl;
    vector<int> dl/*deapest leaf*/, d, p;
    ladder(const vector<vector<int>>& adj) : n(int(ssize(adj))), l_tbl(n), dl(n), d(n), p(n, -1) {
        iota(begin(dl), end(dl), 0);
        for (int i = 0; i < n; i++)
            if (p[i] == -1)
                p[i] = i, dfs(adj, i);
        b_tbl = treeJump(p);
        for (int i = 0; i < n; i++)
            if (p[i] == i || dl[p[i]] != dl[i]) {
                int leaf = dl[i], len = min(2 * (d[leaf] - d[i]), d[leaf]) + 1;
                auto& lad = l_tbl[leaf];
                lad.resize(len, leaf);
                for (int j = 1; j < len; j++)
                    lad[j] = p[lad[j - 1]];
            }
    }
    void dfs(const vector<vector<int>>& adj, int u) {
        for (auto v : adj[u])
            if (v != p[u]) {
                d[v] = d[p[v] = u] + 1;
                dfs(adj, v);
                if (d[dl[v]] > d[dl[u]]) dl[u] = dl[v];
            }
    }
    inline int kth_par(int u, int k) const {
        assert(0 <= k && k <= d[u]);
        if (k == 0) return u;
        int bit = __lg(k);
        u = b_tbl[bit][u], k -= (1 << bit);
        int leaf = dl[u];
        return l_tbl[leaf][k + d[leaf] - d[u]];
    }
};
