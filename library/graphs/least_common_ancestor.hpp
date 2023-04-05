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
	const int N;
	vector<int> in, sz, d, p, tour;
	RMQ<int> rmq;
	LCA(const vector<vector<int>>& adj) :
		N(ssize(adj)), in(N, -1), sz(N, 1), d(N), p(N), rmq(init(adj)) {}
	RMQ<int> init(const vector<vector<int>>& adj) {
		tour.reserve(N);
		for(int i = 0; i < N; i++)
			if(in[i] == -1) dfs(adj, i, -1);
		return RMQ<int>(tour, [&](int u, int v) {
			return pair(d[u], -in[u]) < pair(d[v], -in[v]) ? u : v;
		});
	}
	void dfs(const vector<vector<int>>& adj, int u, int par) {
		in[u] = ssize(tour), p[u] = par;
		tour.push_back(u);
		for (int v : adj[u])
			if (v != par)
				d[v] = 1 + d[u], dfs(adj, v, u), sz[u] += sz[v];
	}
	int lca(int u, int v) const {
		if (u == v) return u;
		tie(u, v) = minmax(in[u], in[v]);
		return p[rmq.query(u+1, v+1)];
	}
	int dist_edges(int u, int v) const {return d[u] + d[v] - 2 * d[lca(u, v)];}
	bool in_subtree(int u, int v) const {return in[u] <= in[v] && in[v] < in[u] + sz[u];}
	int first_on_path(int u, int v) const {
		assert(u != v);
		return in_subtree(u, v) ? rmq.query(in[u]+1, in[v]+1) : p[u];
	}
};
