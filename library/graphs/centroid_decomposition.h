#pragma once

#include "find_centroid.h"

struct centroid_decomp {
	vector<vector<int>> adj;
	function<void(const vector<vector<int>>&, int)> func;
	find_centroid find_c;

	centroid_decomp(const vector<vector<int>>& a_adj,
	                const function<void(const vector<vector<int>>&, int)>& a_func)
		: adj(a_adj), func(a_func), find_c(adj.size()) {
		decomp(find_c.centroid(adj, 0));
	}

	void decomp(int root) {
		func(adj, root);
		for (auto v : adj[root]) {
			adj[v].erase(find(adj[v].begin(), adj[v].end(), root));
			decomp(find_c.centroid(adj, v));
		}
	}
};
