#pragma once

// Time complexity O(n) where n is the number of nodes reachable from root in the tree
// Space complexity O(d) where d is maximum depth of any node reachable from root in the tree

// Given an unweighted rooted tree along with the size of each subtree find_centroid will return a centroid in the tree

// see centroid_decomp for example usage
int find_centroid(const vector<vector<int>>& adj, const vector<int>& subtree_sizes, int root) {
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
