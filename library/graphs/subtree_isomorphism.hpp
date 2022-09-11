#pragma once

// Complexity given in terms of n where n is the number of nodes in the tree
// Time complexity O(n log n)
// Space complexity O(n)

// Given an undirected or directed rooted tree
// rooted_subtree_isomorphism classifies each rooted subtree
struct info {
	int num_distinct_subtrees; //0 <= id[i] < num_distinct_subtrees for all i
	vector<int> id; //id[u] == id[v] iff subtree u is isomorphic to subtree v
};

info subtree_iso(const vector<vector<int>>& adj, int root) {
	vector<int> id(adj.size());
	map<vector<int>, int> hashes;
	auto dfs = [&](auto self, int u, int p) -> int {
		vector<int> ch_ids;
		ch_ids.reserve(adj[u].size());
		for (int v : adj[u]) {
			if (v != p)
				ch_ids.push_back(self(self, v, u));
		}
		sort(ch_ids.begin(), ch_ids.end());
		auto it = hashes.find(ch_ids);
		if (it == hashes.end())
			return id[u] = hashes[ch_ids] = hashes.size();
		return id[u] = it->second;
	};
	dfs(dfs, root, root);
	return {(int)hashes.size(), id};
}
