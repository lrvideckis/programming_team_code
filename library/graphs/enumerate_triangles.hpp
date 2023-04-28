/** @file */
#pragma once
/**
 * @author camc
 * @code{.cpp}
 *     enumerate_triangles(edges, n, [&](int u, int v, int w) {
 *         //u, v, w form a triangle
 *     });
 * @endcode
 * @param edges simple undirected graph
 * @param n number of nodes
 * @param f a function run on all length-3-cycles exactly once
 * @time O(n + m ^ (3/2))
 * @memory O(n + m)
 */
template <typename F> void enumerate_triangles(const vector<pair<int, int>>& edges, int n, const F& f) {
    vector<int> deg(n);
    for (auto [u, v] : edges)
        deg[u]++, deg[v]++;
    vector<vector<int>> adj(n);
    for (auto [u, v] : edges) {
        if (tie(deg[u], u) > tie(deg[v], v))
            swap(u, v);
        adj[u].push_back(v);
    }
    vector<bool> seen(n);
    for (auto [u, v] : edges) {
        for (auto w : adj[u])
            seen[w] = 1;
        for (auto w : adj[v])
            if (seen[w])
                f(u, v, w);
        for (auto w : adj[u])
            seen[w] = 0;
    }
}
