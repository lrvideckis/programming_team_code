#pragma once

struct find_centroid {
	vector<int> subtree_sizes;

	find_centroid(int n) : subtree_sizes(n) {}

	int centroid(const vector<vector<int>>& adj, int root) {
		auto calc_subtree_sizes = [&](auto self, int u, int p = -1) -> void {
			subtree_sizes[u] = 1;
			for (auto v : adj[u]) {
				if (v == p)
					continue;
				self(self, v, u);
				subtree_sizes[u] += subtree_sizes[v];
			}
		};
		calc_subtree_sizes(calc_subtree_sizes, root);
		auto dfs = [&](auto self, int u, int p) -> int {
			int biggest_ch = -1;
			for (auto v : adj[u]) {
				if (v == p)
					continue;
				if (biggest_ch == -1 ||
				        subtree_sizes[biggest_ch] < subtree_sizes[v])
					biggest_ch = v;
			}

			if (biggest_ch != -1 &&
			        2 * subtree_sizes[biggest_ch] > subtree_sizes[root])
				return self(self, biggest_ch, u);
			return u;
		};
		return dfs(dfs, root, root);
	}
};
