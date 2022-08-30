#pragma once
#include "find_centroid.h"

// Time complexity O(n log n) where n is the number of nodes in the tree
// Space complexity O(n) where n is the number of nodes in the tree

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
		calc_subtree_sizes(0);
		decomp(find_centroid(adj, subtree_sizes, 0));
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

	void decomp(int root) {
		func(adj, root);
		for (auto v : adj[root]) {
			adj[v].erase(find(adj[v].begin(), adj[v].end(), root));
			calc_subtree_sizes(v);
			decomp(find_centroid(adj, subtree_sizes, v));
		}
	}
};
