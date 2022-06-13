#pragma once
#include "bridges_and_cuts.h"
//library checker tests: https://judge.yosupo.jp/problem/biconnected_components
//(asserts checking correctness of commented-example-usage-loops)
//returns adjacency list of block vertex tree
//usage:
//	info cc = bridge_and_cut(adj, m);
//	vector<vector<int>> bvt = block_vertex_tree(adj, cc);
//to loop over each *unique* bcc containing a node v:
//	for(int bccid : bvt[v]) {
//		bccid -= n;
//		...
//	}
//to loop over each *unique* node inside a bcc:
//	for(int v : bvt[bccid + n]) {
//		...
//	}
vector<vector<int>> block_vertex_tree(const vector<vector<pair<int, int>>>& adj, const info& cc) {
	int n = adj.size();
	vector<vector<int>> tree(n + cc.num_bccs);
	vector<int> cnt(cc.num_bccs, 0);
	for (int v = 0; v < n; v++) {
		for (auto [_, e_id] : adj[v]) {
			int bccid = cc.bcc_id[e_id];
			if (cnt[bccid]++ == 0) {
				tree[v].push_back(bccid + n);// add edge between original node, and bcc node
				tree[bccid + n].push_back(v);
			}
		}
		for (auto [_, e_id] : adj[v])
			cnt[cc.bcc_id[e_id]]--;
	}
	return tree;
}
