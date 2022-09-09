#pragma once

// Time and Space complexity are given in terms of n where n is the number of nodes in the tree
// Time complexity O(n log n)
// Space complexity O(n)

// Given an unweighted tree with undirected edges and a function centroid_decomp
// implements the function on every decomposition

// see count_paths_per_node for example usage
struct centroid_decomp {
	vector<vector<int>> adj;
	function<void(const vector<vector<int>>&, int)> func;
	vector<int> subtree_sizes;

	centroid_decomp(const vector<vector<int>>& a_adj,
	                const function<void(const vector<vector<int>>&, int)>& a_func)
		: adj(a_adj), func(a_func), subtree_sizes(adj.size()) {
		decomp(find_centroid(0));
	}

	void calc_subtree_sizes(int u, int p = -1) {
		subtree_sizes[u] = 1;
		for (auto v : adj[u]) {
			if (v == p)
				continue;
			calc_subtree_sizes(v, u);
			subtree_sizes[u] += subtree_sizes[v];
		}
	}

	int find_centroid(int root) {
		calc_subtree_sizes(root);
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

	void decomp(int root) {
		func(adj, root);
		for (auto v : adj[root]) {
			//each node is adjacent to O(logn) centroids
			adj[v].erase(find(adj[v].begin(), adj[v].end(), root));
			decomp(find_centroid(v));
		}
	}
};
