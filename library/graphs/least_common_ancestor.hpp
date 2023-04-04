/** @file */
#pragma once
/**
 * Description: Answers lowest common ancestor
 * queries on a rooted tree using RMQ. Works with
 * both directed and undirected adjacency lists.
 * Time: $O(1)$ queries with an $O(n \log{n})$ precomp (RMQ).
 */
#include "../data_structures/sparse_table.hpp"
struct LCA {
	int T = 0;
	vector<int> in, out, d, p, tour;
	RMQ<int> rmq_lca, rmq_path;
	LCA(const vector<vector<int>>& adj) :
		in(ssize(adj)),
		out(in),
		d(in),
		p(in),
		rmq_lca((dfs(adj, 0, -1), tour), [&](int u, int v) {return in[u] < in[v] ? u : v;}),
		rmq_path(tour, [&](int u, int v) {return pair(d[u], -u) < pair(d[v], -v) ? u : v;}) {}
	void dfs(const vector<vector<int>>& adj, int u, int par) {
		in[u] = T++, p[u] = par;
		for (int v : adj[u])
			if (v != par)
				d[v] = 1 + d[u], tour.push_back(u), dfs(adj, v, u);
		out[u] = T;
	}
	int lca(int u, int v) const {
		if (u == v) return u;
		tie(u, v) = minmax(in[u], in[v]);
		return rmq_lca.query(u, v);
	}
	/*
	int size_subtree(int u) const {return out[u] - in[u];}
	bool in_subtree(int u, int v) const {return in[u] <= in[v] && in[v] < out[u];}
	int dist_edges(int u, int v) const {return d[u] + d[v] - 2 * d[lca(u, v)];}
	int first_on_path(int u, int v) const {
		assert(u != v);
		return in_subtree(u, v) ? rmq_path.query(u, v) : p[u];
	}
	*/
};
