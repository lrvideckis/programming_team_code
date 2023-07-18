/** @file */
#pragma once
/**
 * @see https://github.com/ucf-programming-team/hackpack-cpp /blob/master/content/graphs/TreeLifting.h
 * Calculate jumps up a tree, to support fast upward jumps and LCAs.
 */
struct tree_lift {
    int n;
    /**
     * d = depth, p = parent, j = jump
     * @{
     */
    vector<int> d, p, j;
    /** @} */
    /**
     * @param adj forest (rooted or unrooted)
     * @time O(n)
     * @space O(n) for d, p, j vectors
     */
    tree_lift(const vector<vector<int>>& adj): n(ssize(adj)), d(n), p(n, -1), j(n, -1) {
        for (int i = 0; i < n; i++)
            if (j[i] == -1)
                j[i] = i, dfs(adj, i);
    }
    void dfs(const vector<vector<int>>& adj, int u) {
        int jmp = (d[u] + d[j[j[u]]] == 2 * d[j[u]]) ? j[j[u]] : u;
        for (auto v : adj[u])
            if (v != p[u])
                d[v] = d[p[v] = u] + 1, j[v] = jmp, dfs(adj, v);
    }
};
/**
 * copy into main, after initializing `adj`
 */
tree_lift tl(adj);
