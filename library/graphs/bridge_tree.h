#pragma once
#include "bridges_and_cuts.h"
//never adds multiple edges as bridges_and_cuts.h correctly marks them as non-bridges
//usage:
//	info cc = bridge_and_cut(adj, m);
//	vector<vector<int>> bt = bridge_tree(adj, cc);
vector<vector<int>> bridge_tree(const vector<vector<pair<int, int>>>& adj, const info& cc) {
	vector<vector<int>> tree(cc.num_2_edge_ccs);
	for (int i = 0; i < (int)adj.size(); i++)
		for (auto [to, e_id] : adj[i])
			if (cc.is_bridge[e_id])
				tree[cc.two_edge_ccid[i]].push_back(cc.two_edge_ccid[to]);
	return tree;
}
