/** @file */
#pragma once
/**
 * @see https://github.com/kth-competitive-programming /kactl/blob/main/content/graph/SCC.h
 * @code{.cpp}
       auto [num_sccs, scc_id] = sccs(adj);
 * @endcode
 */
struct sccs {
    int num_sccs = 0; /**< number of SCCs */
    /**
     * scc_id[u] = id of SCC containing node u. It satisfies:
     * - 0 <= scc_id[u] < num_sccs
     * - for each edge u -> v: scc_id[u] >= scc_id[v]
     */
    vector<int> scc_id;
    /**
     * @param adj directed, unweighted graph
     * @time O(n + m)
     * @space this allocates member `scc_id` which is O(n)
     */
    sccs(const vector<vector<int>>& adj) : scc_id(ssize(adj), -1) {
        int n = ssize(adj), timer = 1;
        vector<int> tin(n), node_stack;
        node_stack.reserve(n);
        auto dfs = [&](auto&& self, int u) -> int {
            int low = tin[u] = timer++;
            node_stack.push_back(u);
            for (int v : adj[u])
                if (scc_id[v] < 0)
                    low = min(low, tin[v] ? tin[v] : self(self, v));
            if (tin[u] == low) {
                while (1) {
                    int node = node_stack.back();
                    node_stack.pop_back();
                    scc_id[node] = num_sccs;
                    if (node == u) break;
                }
                num_sccs++;
            }
            return low;
        };
        for (int i = 0; i < n; i++)
            if (!tin[i]) dfs(dfs, i);
    }
};
