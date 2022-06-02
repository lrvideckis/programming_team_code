#pragma once
//library checker tests: https://judge.yosupo.jp/problem/frequency_table_of_tree_distance
//with asserts checking depth of tree <= log2(n)

//returns array `par` where `par[i]` = parent of node `i` in centroid tree
//`par[root]` is -1
//0-based nodes
//O(n log n)

//example usage:
//	vector<int> parent = getCentroidTree(adj);
//	vector<vector<int>> childs(n);
//	int root;
//	for (int i = 0; i < n; i++) {
//		if (parent[i] == -1)
//			root = i;
//		else
//			childs[parent[i]].push_back(i);
//	}
vector<int> getCentroidTree(const vector<vector<int>>& adj/*unrooted tree*/) {
	int n = adj.size();
	vector<int> sizes(n);
	vector<bool> vis(n, false);
	auto dfsSz = [&](auto self, int node, int par) -> void {
		sizes[node] = 1;
		for (int to : adj[node]) {
			if (to != par && !vis[to]) {
				self(self, to, node);
				sizes[node] += sizes[to];
			}
		}
	};
	auto findCentroid = [&](int node) -> int {
		dfsSz(dfsSz, node, node);
		int sizeCap = sizes[node] / 2, par = -1;
		while (true) {
			bool found = false;
			for (int to : adj[node]) {
				if (to != par && !vis[to] && sizes[to] > sizeCap) {
					found = true;
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
		node = findCentroid(node);
		parent[node] = par;
		vis[node] = true;
		for (int to : adj[node]) {
			if (!vis[to])
				self(self, to, node);
		}
	};
	dfs(dfs, 0, -1);
	return parent;
}
