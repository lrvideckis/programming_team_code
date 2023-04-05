/** @file */
#pragma once
#include "../data_structures/sparse_table.hpp"
/**
 * @see https://github.com/kth-competitive-programming/
 * kactl/blob/main/content/graph/LCA.h
 */
//NOLINTNEXTLINE(readability-identifier-naming)
struct LCA {
	const int N;
	/**
	 * time in, subtree size, depth, parent, node order of euler tour
	 * @{
	 */
	vector<int> in, sz, d, p, tour;
	/** @} */
	RMQ<int> rmq;
	/**
	 * @param adj forest
	 * @time O(n log n)
	 * @memory O(n log n)
	 */
	LCA(const vector<vector<int>>& adj) : N(ssize(adj)), in(N, -1), sz(N, 1), d(N), p(N), rmq(init(adj)) {}
	RMQ<int> init(const vector<vector<int>>& adj) {
		tour.reserve(N);
		for (int i = 0; i < N; i++)
			if (in[i] == -1) dfs(adj, i, -1);
		return {tour, [&](int u, int v) {return pair(d[u], -in[u]) < pair(d[v], -in[v]) ? u : v;}};
	}
	void dfs(const vector<vector<int>>& adj, int u, int par) {
		in[u] = ssize(tour), p[u] = par;
		tour.push_back(u);
		for (int v : adj[u])
			if (v != par)
				d[v] = 1 + d[u], dfs(adj, v, u), sz[u] += sz[v];
	}
	/**
	 * @param u,v 2 nodes in the same component
	 * @returns lca of u, v
	 * @time O(1)
	 */
	int lca(int u, int v) const {
		if (u == v) return u;
		tie(u, v) = minmax(in[u], in[v]);
		return p[rmq.query(u + 1, v + 1)];
	}
	/**
	 * @param u,v endpoint nodes of path
	 * @returns number of edges on path
	 * @time O(1)
	 */
	int dist_edges(int u, int v) const {return d[u] + d[v] - 2 * d[lca(u, v)];}
	/**
	 * @param u,v 2 nodes
	 * @returns 1 iff v is in u's subtree
	 * @time O(1)
	 */
	bool in_subtree(int u, int v) const {return in[u] <= in[v] && in[v] < in[u] + sz[u];}
	/**
	 * @see https://codeforces.com/blog/entry/71567?#comment-559285
	 * @code{.cpp}
	 *     int u, v; //to loop over all nodes (except v) on path from u to v:
	 *     for (int i = u; i != v; i = lca.next_on_path(i, v)) {}
	 * @endcode
	 * @param u,v endpoint nodes of path
	 * @returns node at index 1 in {u,p[u],..,lca(u,v),..,p[v],v}
	 * @time O(1)
	 */
	int next_on_path(int u, int v) const {
		assert(u != v);
		return in_subtree(u, v) ? rmq.query(in[u] + 1, in[v] + 1) : p[u];
	}
};
