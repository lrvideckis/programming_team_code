/** @file */
#pragma once
#include "../data_structures/sparse_table.hpp"
/**
 * @see https://github.com/kth-competitive-programming /kactl/blob/main/content/graph/LCA.h
 */
//NOLINTNEXTLINE(readability-identifier-naming)
struct LCA {
    int n;
    /**
     * time in, subtree size, depth, parent, pre order traversal
     * note: in[order[i]] = i, order[in[i]] = i
     * @{
     */
    vector<int> in, sub_sz, d, p, order;
    /** @} */
    RMQ<int> rmq;
    /**
     * @param adj forest (rooted or unrooted)
     * @time O(n log n)
     * @space O(n log n) for rmq, all other vectors are O(n)
     */
    LCA(const vector<vector<int>>& adj) : n(ssize(adj)), in(n), sub_sz(n, 1), d(n), p(n, -1) {
        order.reserve(n);
        for (int i = 0; i < n; i++)
            if (p[i] == -1) dfs(adj, i);
        rmq = RMQ<int>(order, [&](int u, int v) {return pair(d[u], -in[u]) < pair(d[v], -in[v]) ? u : v;});
    }
    void dfs(const vector<vector<int>>& adj, int u) {
        in[u] = ssize(order), order.push_back(u);
        for (auto v : adj[u])
            if (v != p[u])
                d[v] = d[p[v] = u] + 1, dfs(adj, v), sub_sz[u] += sub_sz[v];
    }
    /**
     * @param u,v 2 nodes in the same component
     * @returns lca of u, v
     * @time O(1)
     * @space O(1)
     */
    inline int lca(int u, int v) const {
        if (u == v) return u;
        auto [x, y] = minmax(in[u], in[v]);
        return p[rmq.query(x + 1, y + 1)];
    }
    /**
     * @param u,v endpoint nodes of path
     * @returns number of edges on path
     * @time O(1)
     * @space O(1)
     */
    inline int dist_edges(int u, int v) const {return d[u] + d[v] - 2 * d[lca(u, v)];}
    /**
     * @param u,v 2 nodes
     * @returns 1 iff v is in u's subtree
     * @time O(1)
     * @space O(1)
     */
    inline bool in_subtree(int u, int v) const {return in[u] <= in[v] && in[v] < in[u] + sub_sz[u];}
    /**
     * @see https://codeforces.com/blog/entry/71567?#comment-559285
     * @code{.cpp}
     *     int u, v; //to loop over all nodes (except v) on path from u to v:
     *     for (int i = u; i != v; i = lca.next_on_path(i, v)) {}
     * @endcode
     * @param u,v endpoint nodes of path
     * @returns the node vector<int>({u,p[u],..,lca(u,v),..,p[v],v})[1]
     * @time O(1)
     * @space O(1)
     */
    inline int next_on_path(int u, int v) const {
        assert(u != v);
        return in_subtree(u, v) ? rmq.query(in[u] + 1, in[v] + 1) : p[u];
    }
};
