#pragma once
#include "bridges_and_cuts.h"
// status: not tested
// returns adjacency list of block vertex tree
// usage:
//	info cc = bridge_and_cut(adj, m);
//	vector<vector<int>> bvt = block_vertex_tree(adj, cc);
vector<vector<int>> block_vertex_tree(const vector<vector<pair<int, int>>>& adj, const info& cc) {
	int n = adj.size();
	vector<vector<int>> tree(n + cc.numBCCs);
	vector<int> cnt(cc.numBCCs, 0);
	for (int i = 0; i < n; i++) {
		for (auto [to, eId] : adj[i]) {
			int bcc = cc.bccID[eId];
			if (cnt[bcc]++ == 0) {
				tree[i].push_back(bcc + n); // Add edge between each original node, and each BCC node
				tree[bcc + n].push_back(i);
			}
		}
		for (auto [to, eId] : adj[i])
			cnt[cc.bccID[eId]]--;
	}
	return tree;
}
