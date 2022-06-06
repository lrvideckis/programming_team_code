#pragma once
#include "bridges_and_cuts.h"
//library checker tests: https://judge.yosupo.jp/problem/biconnected_components
//(asserts checking correctness of commented-loops)
//returns adjacency list of block vertex tree
//usage:
//	info cc = bridge_and_cut(adj, m);
//	vector<vector<int>> bvt = block_vertex_tree(adj, cc);
//to loop over each *unique* BCC for a node i:
//	for(int bccid : bvt[i]) {
//		bccid -= n;
//		...
//	}
//to loop over each *unique* node for a BCC:
//	for(int i : bvt[bccid + n]) {
//		...
//	}
vector<vector<int>> block_vertex_tree(const vector<vector<pair<int, int>>>& adj, const info& cc) {
	int n = adj.size();
	vector<vector<int>> tree(n + cc.numBCCs);
	vector<int> cnt(cc.numBCCs, 0);
	for (int i = 0; i < n; i++) {
		for (auto [_, eId] : adj[i]) {
			int bcc = cc.bccID[eId];
			if (cnt[bcc]++ == 0) {
				tree[i].push_back(bcc + n);// Add edge between original node, and BCC node
				tree[bcc + n].push_back(i);
			}
		}
		for (auto [_, eId] : adj[i])
			cnt[cc.bccID[eId]]--;
	}
	return tree;
}
