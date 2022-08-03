#pragma once
#include "lca.h"
struct kth_node_on_path {
	LCA lca;
	kth_node_on_path(const vector<vector<pair<int, long long>>>& adj, int root) : lca(adj, root) {}
	//consider path {u, u's par, ..., LCA(u,v), ..., v's par, v}. This returns the node at index k
	//assumes 0 <= k <= number of edges on path from u to v
	int query(int u, int v, int k) const {
		int lca_uv = lca.get_lca(u, v);
		int u_lca = lca.tree[u].depth - lca.tree[lca_uv].depth;
		int v_lca = lca.tree[v].depth - lca.tree[lca_uv].depth;
		assert(0 <= k && k <= u_lca + v_lca);
		return k <= u_lca ? lca.kth_par(u, k) : lca.kth_par(v, u_lca + v_lca - k);
	}
};
