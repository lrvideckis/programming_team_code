/** @file */
#pragma once
#include "centroid_decomp.hpp"
/**
 * @param adj unrooted, connected forest
 * @param k number of edges
 * @returns array `num_paths` where `num_paths[i]` = number of paths with k
 * edges where node `i` is on the path. 0-based nodes.
 * @time O(n log n)
 * @space this function allocates/returns various vectors which are all O(n)
 */
vector<long long> count_paths_per_node(const vector<vector<int>>& adj, int k) {
    vector num_paths(ssize(adj), 0LL);
    centroid(adj, [&](const vector<vector<int>>& cd_adj, int cent) -> void {
        vector pre_d{1}, cur_d{0};
        auto dfs = [&](auto&& self, int u, int p, int d) -> long long {
            if (d > k) return 0;
            if (ssize(cur_d) <= d) cur_d.push_back(0);
            cur_d[d]++;
            auto cnt = 0LL;
            if (k - d < ssize(pre_d)) cnt += pre_d[k - d];
            for (int v : cd_adj[u])
                if (v != p)
                    cnt += self(self, v, u, d + 1);
            num_paths[u] += cnt;
            return cnt;
        };
        auto dfs_child = [&](int child) -> long long {
            auto cnt = dfs(dfs, child, cent, 1);
            pre_d.resize(ssize(cur_d));
            for (int i = 1; i < ssize(cur_d) && cur_d[i]; i++)
                pre_d[i] += cur_d[i], cur_d[i] = 0;
            return cnt;
        };
        for (int child : cd_adj[cent])
            num_paths[cent] += dfs_child(child);
        pre_d = cur_d = {0};
        for_each(rbegin(cd_adj[cent]), rend(cd_adj[cent]), dfs_child);
    });
    return num_paths;
}
