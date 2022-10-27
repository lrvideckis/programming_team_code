#pragma once

// Time and Space complexity are given in terms of n where n is the number of nodes in the forest
// Time complexity O(n log n)
// Space complexity O(n)

// Given an unweighted, undirected forest and a function,
// centroid_decomp runs the function on every decomposition

// Example usage:
//	centroid_decomp decomp(adj, [&](const vector<vector<int>>& adj_removed_edges, int centroid) -> void {
//		...
//	});
template<typename F> struct centroid_decomp {
	vector<vector<int>> adj;
	F func;
	vector<int> sub_sz;
	centroid_decomp(const vector<vector<int>>& a_adj/*undirected forest*/, const F& a_func)
		: adj(a_adj), func(a_func), sub_sz(ssize(adj), -1) {
		for (int i = 0; i < ssize(adj); i++)
			if (sub_sz[i] == -1)
				decomp(i);
	}
	void calc_subtree_sizes(int u, int p = -1) {
		sub_sz[u] = 1;
		for (int v : adj[u]) {
			if (v == p)
				continue;
			calc_subtree_sizes(v, u);
			sub_sz[u] += sub_sz[v];
		}
	}
	void decomp(int u) {
		calc_subtree_sizes(u);
		for (int p = -1, sz_root = sub_sz[u];;) {
			auto big_ch = find_if(adj[u].begin(), adj[u].end(), [&](int v) -> bool {
				return v != p && 2 * sub_sz[v] > sz_root;
			});
			if (big_ch == adj[u].end())
				break;
			p = u;
			u = *big_ch;
		}
		func(adj, u);
		for (int v : adj[u]) {
			//each node is adjacent to O(logn) centroids
			adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
			decomp(v);
		}
	}
};
