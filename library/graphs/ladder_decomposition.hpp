/** @file */
#pragma once
struct ladder_decomp {
    int n;
    vector<vector<int>> jmp/*TODO: swap indexing?*/, ladder;
    vector<int> deapest_leaf, depth;
    ladder_decomp(const vector<vector<int>>& adj) : n(int(ssize(adj))), jmp(1, vector<int>(n, -1)), ladder(n), deapest_leaf(n), depth(n) {
        for (int i = 0; i < n; i++)
            if (jmp[0][i] == -1) {
                jmp[0][i] = i;
                dfs(adj, i);
                ladder[deapest_leaf[i]].resize(2 * depth[deapest_leaf[i]]);
            }
        for (int i = 0; i < n; i++) {
            for(int j = 0, u = i; j < ssize(ladder[i]); j++, u = jmp[0][u]) {//TODO: see if I can remove `u` variable
                ladder[i][j] = u;
            }
        }
        for(int lvl = 0; (2<<lvl) < n; lvl++) {
            jmp.emplace_back(n);
            for (int i = 0; i < n; i++)
                jmp[lvl + 1][i] = jmp[lvl][jmp[lvl][i]];
        }
    }
    void dfs(const vector<vector<int>>& adj, int u) {
        deapest_leaf[u] = u;//TODO iota instead?
        for (auto v : adj[u])
            if (v != jmp[0][u]) {
                jmp[0][v] = u;
                depth[v] = 1 + depth[u];//TODO tree lift style
                dfs(adj, v);
                if(depth[deapest_leaf[v]] > depth[deapest_leaf[u]]) {
                    deapest_leaf[u] = deapest_leaf[v];
                }
            }
        for (auto v : adj[u])//TODO see if we can do this in a single loop above
            if (v != jmp[0][u]) {
                if (deapest_leaf[u] != deapest_leaf[v]) {
                    ladder[deapest_leaf[v]].resize(2 * (depth[deapest_leaf[v]] - depth[v]));//TODO: don't allocate more memory if the ladder goes past the root
                }
            }
    }
    inline int kth_par(int u, int k) const {
        assert(k <= depth[u]);//TODO: how to handle if k > depth[u]?
        assert(k >= 0);
        if(k==0) return u;//TODO not have this special case?
        int bit = __lg(k);
        assert((k>>bit)&1);
        assert(bit < ssize(jmp));
        u = jmp[bit][u];
        k -= (1<<bit);
        if(k == 0) return u;//TODO not have this special case?
        int leaf = deapest_leaf[u];
        k += depth[leaf] - depth[u];
        assert(k < ssize(ladder[leaf]));
        return ladder[leaf][k];
    }
};
