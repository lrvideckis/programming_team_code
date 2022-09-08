#pragma once

// Complexity given in terms of n where n is the number of nodes in the tree
// Time complexity O(n log n)
// Space complexity O(n)

// Given an undirected or directed rooted tree
// rooted_subtree_isomorphism classifies each rooted subtree
struct isomorphic_classifications {
	int k;
	vector<int> ids;
	isomorphic_classifications(int n) : ids(n) { }
};

isomorphic_classifications subtree_isomorphism_classification(
    const vector<vector<int>>& adj, int root) {
	isomorphic_classifications classifications(adj.size());
	map<vector<int>, int> hashes;
	auto dfs = [&](auto self, int u, int p) -> int {
		vector<int> ch_ids;
		ch_ids.reserve(adj[u].size());
		for (auto v : adj[u]) {
			if (v != p)
				ch_ids.push_back(self(self, v, u));
		}
		sort(ch_ids.begin(), ch_ids.end());
		auto it = hashes.find(ch_ids);
		if (it == hashes.end())
			return classifications.ids[u] = hashes[ch_ids] = hashes.size();
		return classifications.ids[u] = it->second;
	};
	dfs(dfs, root, root);
	classifications.k = hashes.size();
	return classifications;
}
