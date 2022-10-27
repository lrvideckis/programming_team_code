#pragma once
#include "bridges_and_cuts.hpp"
//returns adjacency list of block vertex tree
//usage:
//	graph_info cc = bridge_and_cut(adj, m);
//	vector<vector<int>> bvt = block_vertex_tree(adj, cc);
//to loop over each *unique* bcc containing a node v:
//	for (int bccid : bvt[v]) {
//		bccid -= n;
//		...
//	}
//to loop over each *unique* node inside a bcc:
//	for (int v : bvt[bccid + n]) {
//		...
//	}
vector<vector<int>> block_vertex_tree(const vector<vector<pair<int, int>>>& adj, const graph_info& cc) {
	int n = ssize(adj);
	vector<vector<int>> bvt(n + cc.num_bccs);
	vector<bool> vis(cc.num_bccs, 0);
	for (int v = 0; v < n; v++) {
		for (auto [_, e_id] : adj[v]) {
			int bccid = cc.bcc_id[e_id];
			if (!vis[bccid]) {
				vis[bccid] = 1;
				bvt[v].push_back(bccid + n);//add edge between original node, and bcc node
				bvt[bccid + n].push_back(v);
			}
		}
		for (int bccid : bvt[v])
			vis[bccid - n] = 0;
	}
	return bvt;
}
