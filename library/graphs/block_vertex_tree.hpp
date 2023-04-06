/** @file */
#pragma once
#include "bridges_and_cuts.hpp"
/**
 * @code{.cpp}
 *     graph_info cc = bridge_and_cut(adj, m);
 *     vector<vector<int>> bvt = block_vertex_tree(adj, cc);
 *
 *     //to loop over each *unique* bcc containing a node u:
 *     for (auto bccid : bvt[u]) {
 *         bccid -= n;
 *     }
 *
 *     //to loop over each *unique* node inside a bcc:
 *     for (auto u : bvt[bccid + n]) {}
 * @endcode
 *
 * [0, n) are original nodes
 * [n, n + num_bccs) are BCC nodes
 *
 * @param adj undirected graph
 * @param cc what's calculated by bridges_and_cuts
 * @returns adjacency list of block vertex tree
 * @time O(n + m)
 * @memory O(n + m)
 */
vector<vector<int>> block_vertex_tree(const vector<vector<pair<int, int>>>& adj, const graph_info& cc) {
	int n = ssize(adj);
	vector<vector<int>> bvt(n + cc.num_bccs);
	vector<bool> vis(cc.num_bccs, 0);
	for (int u = 0; u < n; u++) {
		for (auto [_, e_id] : adj[u]) {
			int bccid = cc.bcc_id[e_id];
			if (!vis[bccid]) {
				vis[bccid] = 1;
				bvt[u].push_back(bccid + n);
				bvt[bccid + n].push_back(u);
			}
		}
		for (auto bccid : bvt[u]) vis[bccid - n] = 0;
	}
	return bvt;
}
