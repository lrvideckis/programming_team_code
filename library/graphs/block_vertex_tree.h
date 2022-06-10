#pragma once
#include "bridges_and_cuts.h"
//library checker tests: https://judge.yosupo.jp/problem/biconnected_components
//(asserts checking correctness of commented-example-usage-loops)
//returns adjacency list of block vertex tree
//usage:
//	info cc = bridge_and_cut(adj, m);
//	vector<vector<int>> bvt = block_vertex_tree(adj, cc);
//to loop over each *unique* BCC containing a node i:
//	for(int bccid : bvt[i]) {
//		bccid -= n;
//		...
//	}
//to loop over each *unique* node inside a BCC:
//	for(int i : bvt[bccid + n]) {
//		...
//	}
vector<vector<int>> block_vertex_tree(const vector<vector<pair<int, int>>>& adj, const info& cc) {
	int n = adj.size();
	vector<vector<int>> tree(n + cc.num_bccs);
	vector<int> cnt(cc.num_bccs, 0);
	for (int i = 0; i < n; i++) {
		for (auto [_, e_id] : adj[i]) {
			int bcc = cc.bcc_id[e_id];
			if (cnt[bcc]++ == 0) {
				tree[i].push_back(bcc + n);// Add edge between original node, and BCC node
				tree[bcc + n].push_back(i);
			}
		}
		for (auto [_, e_id] : adj[i])
			cnt[cc.bcc_id[e_id]]--;
	}
	return tree;
}
