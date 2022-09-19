#pragma once

// Time and Space complexity are given in terms of n where n is the number of nodes in the tree
// Time complexity O(n log n)
// Space complexity O(n)

// Given an unweighted, undirected tree and a function,
// centroid_decomp runs the function on every decomposition

// see count_paths_per_node for example usage
struct centroid_decomp {
	vector<vector<int>> adj;
	function<void(const vector<vector<int>>&, int)> func;
	vector<int> sub_sz;

	centroid_decomp(const vector<vector<int>>& a_adj,
	                const function<void(const vector<vector<int>>&, int)>& a_func)
		: adj(a_adj), func(a_func), sub_sz(adj.size(), -1) {
		for (int i = 0; i < (int)adj.size(); i++)
			if (sub_sz[i] == -1)
				decomp(find_centroid(i));
	}

	void calc_subtree_sizes(int u, int p = -1) {
		sub_sz[u] = 1;
		for (int v : adj[u]) {
			if (v == p) continue;
			calc_subtree_sizes(v, u);
			sub_sz[u] += sub_sz[v];
		}
	}

	int find_centroid(int root) {
		calc_subtree_sizes(root);
		int u = root, p = -1;
		while (1) {
			int big_ch = -1;
			for (int v : adj[u]) {
				if (v == p) continue;
				if (big_ch == -1 || sub_sz[big_ch] < sub_sz[v])
					big_ch = v;
			}
			if (big_ch == -1 || 2 * sub_sz[big_ch] <= sub_sz[root])
				return u;
			p = u;
			u = big_ch;
		}
	}

	void decomp(int root) {
		func(adj, root);
		for (int v : adj[root]) {
			//each node is adjacent to O(logn) centroids
			adj[v].erase(find(adj[v].begin(), adj[v].end(), root));
			decomp(find_centroid(v));
		}
	}
};
