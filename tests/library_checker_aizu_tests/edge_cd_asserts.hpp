#pragma once
void edge_cd_asserts(const vector<vector<int>>& cd_adj, int cent, int split) {
    assert(ssize(cd_adj) > 2);
    assert(0 < split && split < ssize(cd_adj[cent]));
    auto dfs = [&](auto&& self, int u, int p) -> int {
        int siz = 1;
        for (int v : cd_adj[u])
            if (v != p) siz += self(self, v, u);
        return siz;
    };
    int sz_all = dfs(dfs, cent, -1);
    assert(sz_all >= 3);
    array<int, 2> cnts = {0, 0};
    for (int i = 0; i < ssize(cd_adj[cent]); i++) {
        int sz_subtree = dfs(dfs, cd_adj[cent][i], cent);
        assert(2 * sz_subtree <= sz_all);
        cnts[i < split] += sz_subtree;
    }
    assert(cnts[0] + cnts[1] + 1 == sz_all);
    for (int i = 0; i < 2; i++)
        assert(0 < cnts[i] && cnts[i] <= 2 * cnts[!i]);
}
