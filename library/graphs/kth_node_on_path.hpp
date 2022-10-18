#pragma once
#include "lca.hpp"
//consider path {u, u's par, ..., LCA(u,v), ..., v's par, v}. This returns the node at index k
//assumes 0 <= k <= number of edges on path from u to v
// u, v must be in the same component
//
//To loop over all nodes on a path from u to v:
//kth_node_on_path kpath(adj);
//for (int i = 0; i <= kpath.lca.dist_edges(u, v); i++) {
//	int node = kpath.query(u, v, i);
//	...
struct kth_node_on_path {
	LCA lca;
	kth_node_on_path(const vector<vector<pair<int, long long>>>& adj/*forest of weighted trees*/) : lca(adj) {}
	int query(int u, int v, int k) const {
		int lca_uv = lca.get_lca(u, v);
		int u_lca = lca.tree[u].depth - lca.tree[lca_uv].depth;
		int v_lca = lca.tree[v].depth - lca.tree[lca_uv].depth;
		assert(0 <= k && k <= u_lca + v_lca);
		return k <= u_lca ? lca.kth_par(u, k) : lca.kth_par(v, u_lca + v_lca - k);
	}
};
