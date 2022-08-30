#pragma once
#include "centroid_decomposition.h"
//0-based nodes
//returns array `num_paths` where `num_paths[i]` = number of paths with k edges where node `i` is on the path
//O(n log n)
vector<long long> count_paths_per_node(const vector<vector<int>>& a_adj/*unrooted tree*/, int k) {
	vector<long long> num_paths(a_adj.size());
	auto func = [&](const vector<vector<int>>& adj, int root) {
		vector<int> pre_d(1, 1), cur_d(1);
		auto dfs = [&](auto self, int u, int p, int d, int rot) -> long long {
			if (d > k)
				return 0;

			if (int(cur_d.size()) <= d)
				cur_d.push_back(0);
			cur_d[d]++;

			long long cnt = 0;
			if (k - d < int(pre_d.size()))
				cnt += pre_d[k - d];

			auto adj_u = adj[u];
			if (rot == 1)
				reverse(adj_u.begin(), adj_u.end());

			for (int v : adj_u) {
				if (v == p)
					continue;
				cnt += self(self, v, u, d + 1, rot);
				if (u == root) {
					for (int i = 1; i < int(cur_d.size()) && cur_d[i]; i++) {
						if (int(pre_d.size()) <= i)
							pre_d.push_back(0);
						pre_d[i] += cur_d[i];
						cur_d[i] = 0;
					}
				}
			}

			num_paths[u] += cnt;
			return cnt;
		};
		dfs(dfs, root, root, 0, 0);
		pre_d = vector<int>(1);
		cur_d = vector<int>(1);
		num_paths[root] -= dfs(dfs, root, root, 0, 1);
	};
	centroid_decomp decomp(a_adj, func);
	return num_paths;
}
