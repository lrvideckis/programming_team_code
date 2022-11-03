#pragma once
struct iso_info {
	int num_distinct_subtrees; //0 <= id[i] < num_distinct_subtrees
	vector<int> id; //id[u] == id[v] iff rooted subtree u is isomorphic to rooted subtree v
};
/**
 * @brief Rooted Tree Isomorphism
 * @time O(n log n)
 * @memory O(n)
 */
iso_info subtree_iso(const vector<vector<int>>& adj) {
	vector<int> id(ssize(adj), -1);
	map<vector<int>, int> hashes;
	auto dfs = [&](auto self, int u, int p) -> int {
		vector<int> ch_ids;
		ch_ids.reserve(ssize(adj[u]));
		for (int v : adj[u]) {
			if (v != p)
				ch_ids.push_back(self(self, v, u));
		}
		sort(ch_ids.begin(), ch_ids.end());
		auto it = hashes.find(ch_ids);
		if (it == hashes.end())
			return id[u] = hashes[ch_ids] = ssize(hashes);
		return id[u] = it->second;
	};
	for (int i = 0; i < ssize(adj); i++)
		if (id[i] == -1)
			dfs(dfs, i, i);
	return {ssize(hashes), id};
}
