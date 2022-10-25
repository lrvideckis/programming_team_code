#pragma once

// Time and Space complexity are given in terms of n where n is the number of nodes in the forest
// Time complexity O(n log n)
// Space complexity O(n)

// Given an unweighted, undirected forest and a function,
// centroid_decomp runs the function on every decomposition

// see count_paths_per_node for example usage
template<typename F = function<void(const vector<vector<int>>&, int)>>
struct centroid_decomp {
	vector<vector<int>> adj;
	F func;
	vector<int> sub_sz;

	centroid_decomp(const vector<vector<int>>& a_adj, //undirected forest
	                const F& a_func)
		: adj(a_adj), func(a_func), sub_sz(ssize(adj), -1) {
		for (int i = 0; i < ssize(adj); i++)
			if (sub_sz[i] == -1)
				decomp(i);
	}

	void calc_subtree_sizes(int u, int p = -1) {
		sub_sz[u] = 1;
		for (int v : adj[u]) {
			if (v == p) continue;
			calc_subtree_sizes(v, u);
			sub_sz[u] += sub_sz[v];
		}
	}

	void decomp(int u) {
		calc_subtree_sizes(u);
		for(int p = -1, sz_root = sub_sz[u];;) {
			int big_ch = -1;
			for (int v : adj[u]) {
				if (v == p) continue;
				if (big_ch == -1 || sub_sz[big_ch] < sub_sz[v])
					big_ch = v;
			}
			if (big_ch == -1 || 2 * sub_sz[big_ch] <= sz_root)
				break;
			p = u;
			u = big_ch;
		}
		func(adj, u);
		for (int v : adj[u]) {
			//each node is adjacent to O(logn) centroids
			adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
			decomp(v);
		}
	}
};
