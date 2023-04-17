/** @file */
#pragma once
/**
 * @author lightseba
 * @see https://github.com/ucf-programming-team/hackpack-cpp
 * /blob/master/content/graphs/TreeLifting.h
 * Calculate jumps up a tree, to support fast upward jumps and LCAs.
 */
struct tree_lift {
    const int N;
    /**
     * d = depth, p = parent, j = jump
     * @{
     */
    vector<int> d, p, j;
    /** @} */
    /**
     * @param adj forest
     * @time O(n)
     * @memory O(n)
     */
    tree_lift(const vector<vector<int>>& adj): N(ssize(adj)), d(N), p(N, -1), j(N, -1) {
        for (int i = 0; i < N; i++)
            if (j[i] == -1)
                j[i] = i, dfs(adj, i);
    }
    void dfs(const vector<vector<int>>& adj, int u) {
        int jmp = (d[u] + d[j[j[u]]] == 2 * d[j[u]]) ? j[j[u]] : u;
        for (int v : adj[u])
            if (v != p[u])
                d[v] = d[p[v] = u] + 1, j[v] = jmp, dfs(adj, v);
    }
    /**
     * @param u query node
     * @param k number of edges
     * @returns a node k edges up from u. With k=1, this returns u's parent.
     * @time O(log k)
     */
    int kth(int u, int k) const {
        if (k > d[u]) return -1;
        int anc_d = d[u] - k;
        while (d[u] > anc_d) u = d[j[u]] >= anc_d ? j[u] : p[u];
        return u;
    }
    /**
     * @param u,v 2 nodes in the same component
     * @returns lca of u, v
     * @time O(log(path length))
     */
    int lca(int u, int v) const {
        if (d[u] < d[v]) swap(u, v);
        u = kth(u, d[u] - d[v]);
        while (u != v)
            if (j[u] != j[v]) u = j[u], v = j[v];
            else u = p[u], v = p[v];
        return u;
    }
    /**
     * @param u,v endpoint nodes of path
     * @returns number of edges on path
     * @time O(log(path length))
     */
    int dist_edges(int u, int v) const {return d[u] + d[v] - 2 * d[lca(u, v)];}
    /**
     * @param u,v endpoint nodes of path
     * @param k index into path
     * @returns the node vector<int>({u,p[u],..,lca(u,v),..,p[v],v})[k], so u if k=0
     * @time O(log(path length))
     */
    int kth_path(int u, int v, int k) const {
        int lca_d = d[lca(u, v)];
        int u_lca = d[u] - lca_d;
        int v_lca = d[v] - lca_d;
        return k <= u_lca ? kth(u, k) : kth(v, u_lca + v_lca - k);
    }
};
