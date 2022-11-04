#pragma once
#include "centroid_decomposition.hpp"
/**
 * Returns array `num_paths` where `num_paths[i]` = number of paths with k
 * edges where node `i` is on the path. 0-based nodes.
 * @time O(n log n)
 */
vector<long long> count_paths_per_node(const vector<vector<int>>& adj/*unrooted tree*/, int k) {
	vector<long long> num_paths(ssize(adj));
	centroid_decomp decomp(adj, [&](const vector<vector<int>>& adj_removed_edges, int cent) -> void {
		vector<int> pre_d(1, 1), cur_d(1);
		auto dfs = [&](auto self, int u, int p, int d) -> long long {
			if (d > k) return 0;
			if (ssize(cur_d) <= d) cur_d.push_back(0);
			cur_d[d]++;
			long long cnt = 0;
			if (k - d < ssize(pre_d)) cnt += pre_d[k - d];
			for (int v : adj_removed_edges[u])
				if (v != p)
					cnt += self(self, v, u, d + 1);
			num_paths[u] += cnt;
			return cnt;
		};
		auto dfs_child = [&](int child) -> long long {
			long long cnt = dfs(dfs, child, cent, 1);
			pre_d.resize(ssize(cur_d));
			for (int i = 1; i < ssize(cur_d) && cur_d[i]; i++)
				pre_d[i] += cur_d[i], cur_d[i] = 0;
			return cnt;
		};
		for (int child : adj_removed_edges[cent])
			num_paths[cent] += dfs_child(child);
		pre_d = vector<int>(1);
		cur_d = vector<int>(1);
		for (auto it = adj_removed_edges[cent].rbegin(); it != adj_removed_edges[cent].rend(); it++)
			dfs_child(*it);
	});
	return num_paths;
}
