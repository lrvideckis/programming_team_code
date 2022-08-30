#pragma once
#include "../../kactl/content/numerical/FastFourierTransform.h"
#include "centroid_decomposition.h"
//returns array `cnt_paths` where `cnt_paths[i]` = # of paths in tree with `i` edges
//O(n log^2 n)
vector<long long> count_paths_per_length(const vector<vector<int>>& a_adj/*unrooted, connected tree*/) {
	vector<long long> cnt_paths(a_adj.size(), 0);
	auto func = [&](const vector<vector<int>>& adj, int root) {
		vector<double> total_depth(1, 1.0);
		for (int to : adj[root]) {
			vector<double> cnt_depth(1, 0.0);
			for (queue<pair<int, int>> q({{to, root}}); !q.empty();) {
				cnt_depth.push_back(q.size());
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
			{
				vector<double> prod = conv(total_depth, cnt_depth);
				for (int i = 1; i < (int)prod.size(); i++) cnt_paths[i] += llround(prod[i]);
			}
			if (total_depth.size() < cnt_depth.size()) total_depth.resize(cnt_depth.size(), 0.0);
			for (int i = 1; i < (int)cnt_depth.size(); i++) total_depth[i] += cnt_depth[i];
		}
	};
	centroid_decomp decomp(a_adj, func);
	return cnt_paths;
}
