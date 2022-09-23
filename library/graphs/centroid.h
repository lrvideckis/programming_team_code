#pragma once
//returns array `par` where `par[i]` = parent of node `i` in centroid tree
//`par[root]` is -1
//0-based nodes
//O(n log n)
//example usage:
//	vector<int> parent = get_centroid_tree(adj);
//	vector<vector<int>> childs(n);
//	int root;
//	for (int i = 0; i < n; i++) {
//		if (parent[i] == -1)
//			root = i;
//		else
//			childs[parent[i]].push_back(i);
//	}
vector<int> get_centroid_tree(const vector<vector<int>>& adj/*unrooted tree*/) {
	int n = ssize(adj);
	vector<int> sizes(n);
	vector<bool> vis(n, 0);
	auto dfs_sz = [&](auto self, int node, int par) -> void {
		sizes[node] = 1;
		for (int to : adj[node]) {
			if (to != par && !vis[to]) {
				self(self, to, node);
				sizes[node] += sizes[to];
			}
		}
	};
	auto find_centroid = [&](int node) -> int {
		dfs_sz(dfs_sz, node, node);
		int size_cap = sizes[node] / 2, par = -1;
		while (1) {
			bool found = 0;
			for (int to : adj[node]) {
				if (to != par && !vis[to] && sizes[to] > size_cap) {
					found = 1;
					par = node;
					node = to;
					break;
				}
			}
			if (!found) return node;
		}
	};
	vector<int> parent(n);
	auto dfs = [&](auto self, int node, int par) -> void {
		node = find_centroid(node);
		parent[node] = par;
		vis[node] = 1;
		for (int to : adj[node]) {
			if (!vis[to])
				self(self, to, node);
		}
	};
	dfs(dfs, 0, -1);
	return parent;
}
