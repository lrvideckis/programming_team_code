#pragma once
#include "../../kactl/content/numerical/FastFourierTransform.h"
#include "centroid_decomposition.hpp"
//returns array `num_paths` where `num_paths[i]` = # of paths in tree with `i` edges
//O(n log^2 n)
vector<long long> count_paths_per_length(const vector<vector<int>>& a_adj/*unrooted, connected tree*/) {
	vector<long long> num_paths(ssize(a_adj), 0);
	auto func = [&](const vector<vector<int>>& adj, int root) -> void {
		vector<vector<double>> child_depths;
		for (int to : adj[root]) {
			child_depths.emplace_back(1, 0.0);
			for (queue<pair<int, int>> q({{to, root}}); !q.empty();) {
				child_depths.back().push_back(ssize(q));
				queue<pair<int, int>> new_q;
				while (!q.empty()) {
					auto [curr, par] = q.front();
					q.pop();
					for (int ch : adj[curr]) {
						if (ch == par) continue;
						new_q.emplace(ch, curr);
					}
				}
				swap(q, new_q);
			}
		}
		sort(child_depths.begin(), child_depths.end(), [&](const auto& x, const auto& y) {
			return x.size() < y.size();
		});
		vector<double> total_depth(1, 1.0);
		for (const auto& cnt_depth : child_depths) {
			vector<double> prod = conv(total_depth, cnt_depth);
			for (int i = 1; i < ssize(prod); i++)
				num_paths[i] += llround(prod[i]);
			total_depth.resize(ssize(cnt_depth), 0.0);
			for (int i = 1; i < ssize(cnt_depth); i++)
				total_depth[i] += cnt_depth[i];
		}
	};
	centroid_decomp decomp(a_adj, func);
	return num_paths;
}
