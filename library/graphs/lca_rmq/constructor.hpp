/** @file */
#pragma once
#include "../../data_structures/sparse_table.hpp"
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
};
