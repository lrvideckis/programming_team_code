/** @file */
#pragma once
/**
 * @author lightseba
 * @see https://github.com/ucf-programming-team/hackpack-cpp
 * /blob/master/content/graphs/TreeLifting.h
 * Calculate jumps up a tree, to support fast upward jumps and LCAs.
 */
struct tree_lift {
	/**
	 * d = depth, p = parent, j = jump
	 */
	/** @{ */
	vector<int> d, p, j;
	/** @} */
	/**
	 * @param adj undirected forest
	 * @time O(n)
	 * @memory O(n)
	 */
	tree_lift(const vector<vector<int>>& adj): d(ssize(adj)), p(d), j(d) {
		dfs(0, adj);//TODO make it work on a forest
	}
	void dfs(int u, const vector<vector<int>>& adj) {
		int jmp = (d[u] + d[j[j[u]]] == 2 * d[j[u]]) ? j[j[u]] : u;
		for (int v : adj[u])
			if (v != p[u])
				d[v] = d[p[v] = u] + 1, j[v] = jmp, dfs(v, adj);
	}
	/**
	 * @param u query node
	 * @param k number of edges
	 * @returns a node k edges up from u. With k=1, this returns u's parent.
	 * @time O(log k)
	 */
	int kth(int u, int k) const {
		if (k > d[u]) return -1;
		k = d[u] - k;
		while (d[u] > k) u = d[j[u]] >= k ? j[u] : p[u];
		return u;
	}
	/**
	 * @param u,v 2 nodes in the same component
	 * @returns lca of u, v
	 * @time O(log n)
	 */
	int lca(int u, int v) const {
		if (d[u] < d[v]) swap(u, v);
		while (d[u] > d[v]) u = d[j[u]] >= d[v] ? j[u] : p[u];
		if (u == v) return u;
		while (p[u] != p[v])
			if (j[u] != j[v]) u = j[u], v = j[v];
			else u = p[u], v = p[v];
		return p[u];
	}
	/**
	 * @param u,v endpoint nodes of path
	 * @returns number of edges on path
	 * @time O(log n)
	 */
	int dist_edges(int u, int v) const {return d[u] + d[v] - 2 * d[lca(u, v)];}
	/**
	 * @param u,v endpoint nodes of path
	 * @param k index into path
	 * @returns the node at index k in [u,..,LCA(u,v),..,v], so u if k=0
	 * @time O(log n)
	 */
	int kth_path(int u, int v, int k) const {
		int lca_uv = lca(u, v);
		int u_lca = d[u] - d[lca_uv];
		int v_lca = d[v] - d[lca_uv];
		assert(0 <= k && k <= u_lca + v_lca);
		return k <= u_lca ? kth(u, k) : kth(v, u_lca + v_lca - k);
	}
};
