/** @file */
#pragma once
#include "scc.hpp"
/**
 * @see https://codeforces.com/blog/entry/15102
 *
 * Minimum extra directed edges to add to directed graph to make it strongly connected.
 * If the directed graph is not initially strongly connected, then the edge
 * list's size is max(# zero indegree SCCs, # zero outdegree SCCs)
 *
 * @code{.cpp}
 *     vector<vector<int>> adj;
 *     auto [num_sccs, scc_id] = get_sccs(adj);
 *     vector<pair<int, int>> edges = extra_edges(adj, num_sccs, scc_id);
 * @endcode
 * @param adj,num_sccs,scc_id directed graph and its SCCs
 * @returns directed edge list: edges[i].first -> edges[i].second
 * @time O(n + m)
 * @space O(n + m) TODO
 */
vector<pair<int, int>> extra_edges(const vector<vector<int>>& adj, int num_sccs, const vector<int>& scc_id) {
    if (num_sccs == 1) return {};
    int n = ssize(adj);
    vector<vector<int>> scc_adj(num_sccs);
    vector<int> in_deg(num_sccs);
    for (int i = 0; i < n; i++) {
        for (int v : adj[i]) {
            if (scc_id[i] == scc_id[v]) continue;
            scc_adj[scc_id[i]].push_back(scc_id[v]);
            in_deg[scc_id[v]]++;
        }
    }
    //since {num_sccs-1, ..., 2, 1, 0} is a topo order
    assert(scc_adj[0].empty() && in_deg[num_sccs-1] == 0);
    vector<pair<int, int>> res_edges;
    vector<bool> vis(num_sccs);
    auto dfs = [&](auto&& self, int u) -> int {
        if (scc_adj[u].empty()) return u;
        for (int v : scc_adj[u]) {
            if (!vis[v]) {
                vis[v] = 1;
                int zero_out_node = self(self, v);
                //important: break out the moment we find the first zero out degree
                //WA if this isn't here, reason: complicated
                if (zero_out_node != -1) return zero_out_node;
            }
        }
        return -1;
    };
    vector<pair<int, int>> blocking_matching;
    vector<bool> node_used(num_sccs);
    for (int i = 0; i < num_sccs; i++) {
        if (!in_deg[i]) {
            if (!vis[i]) {
                vis[i] = 1;
                int zero_out_node = dfs(dfs, i);
                if (zero_out_node != -1) {
                    blocking_matching.emplace_back(i, zero_out_node);
                    node_used[i] = 1;
                    node_used[zero_out_node] = 1;
                }
            }
        }
    }
    for (int i = 1; i < ssize(blocking_matching); i++)
        res_edges.emplace_back(blocking_matching[i].second, blocking_matching[i - 1].first);
    res_edges.emplace_back(blocking_matching[0].second, blocking_matching.back().first);
    queue<int> in_unused, out_unused;
    for (int i = 0; i < num_sccs; i++) {
        if (!in_deg[i] && !node_used[i]) in_unused.push(i);
        if (scc_adj[i].empty() && !node_used[i]) out_unused.push(i);
    }
    while (!in_unused.empty() && !out_unused.empty()) {
        res_edges.emplace_back(out_unused.front(), in_unused.front());
        in_unused.pop();
        out_unused.pop();
    }
    while (!in_unused.empty()) {
        res_edges.emplace_back(0, in_unused.front());
        in_unused.pop();
    }
    while (!out_unused.empty()) {
        res_edges.emplace_back(out_unused.front(), num_sccs - 1);
        out_unused.pop();
    }
    vector<int> to_a_node(num_sccs);
    for (int i = 0; i < n; i++)
        to_a_node[scc_id[i]] = i;
    for (auto& [u, v] : res_edges) {
        u = to_a_node[u];
        v = to_a_node[v];
    }
    return res_edges;
}
