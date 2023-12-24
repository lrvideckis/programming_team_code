/** @file */
#pragma once
#include "../../../kactl/content/numerical/FastFourierTransform.h"
#include "centroid_decomp.hpp"
/**
 * @param adj unrooted, connected forest
 * @returns array `num_paths` where `num_paths[i]` = # of paths in tree with `i`
 * edges. `num_paths[1]` = # edges
 * @time O(n log^2 n)
 * @space this function allocates/returns various vectors which are each O(n)
 */
vector<long long> count_paths_per_length(const vector<vector<int>>& adj) {
    vector num_paths(ssize(adj), 0LL);
    centroid(adj, [&](const vector<vector<int>>& adj_cd, int cent) -> void {
        vector<vector<double>> child_depths;
        for (int u : adj_cd[cent]) {
            child_depths.emplace_back(1, 0.0);
            for (queue<array<int, 2>> q({{u, cent}}); !empty(q);) {
                child_depths.back().push_back(int(ssize(q)));
                queue<array<int, 2>> new_q;
                while (!empty(q)) {
                    auto [v, p] = q.front();
                    q.pop();
                    for (int w : adj_cd[v]) {
                        if (w == p) continue;
                        new_q.push({w, v});
                    }
                }
                swap(q, new_q);
            }
        }
        sort(begin(child_depths), end(child_depths), [&](auto & x, auto & y) {
            return ssize(x) < ssize(y);
        });
        vector total_depth(1, 1.0);
        for (auto& cnt_depth : child_depths) {
            auto prod = conv(total_depth, cnt_depth);
            for (int i = 1; i < ssize(prod); i++)
                num_paths[i] += llround(prod[i]);
            total_depth.resize(ssize(cnt_depth));
            for (int i = 1; i < ssize(cnt_depth); i++)
                total_depth[i] += cnt_depth[i];
        }
    });
    return num_paths;
}
