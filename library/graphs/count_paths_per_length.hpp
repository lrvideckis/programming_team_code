/** @file */
#pragma once
#include "../../kactl/content/numerical/FastFourierTransform.h"
#include "centroid_decomposition.hpp"
/**
 * @param adj unrooted, connected forest
 * @returns array `num_paths` where `num_paths[i]` = # of paths in tree with `i`
 * edges. `num_paths[1]` = # edges
 * @time O(n log^2 n)
 * @memory O(n)
 */
vector<long long> count_paths_per_length(const vector<vector<int>>& adj) {
	vector<long long> num_paths(ssize(adj));
	centroid_decomp(adj, [&](const vector<vector<int>>& adj_removed_edges, int cent) -> void {
		vector<vector<double>> child_depths;
		for (auto u : adj_removed_edges[cent]) {
			child_depths.emplace_back(1, 0.0);
			for (queue<pair<int, int>> q({{u, cent}}); !q.empty();) {
				child_depths.back().push_back(ssize(q));
				queue<pair<int, int>> new_q;
				while (!q.empty()) {
					auto [v, p] = q.front();
					q.pop();
					for (auto w : adj_removed_edges[v]) {
						if (w == p) continue;
						new_q.emplace(w, v);
					}
				}
				swap(q, new_q);
			}
		}
		sort(child_depths.begin(), child_depths.end(), [&](const auto & x, const auto & y) {
			return ssize(x) < ssize(y);
		});
		vector<double> total_depth(1, 1.0);
		for (const auto& cnt_depth : child_depths) {
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
