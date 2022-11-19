#pragma once
/**
 * Given an edge list representing an undirected graph and a function, 'enumerate_triangles' will
 * call the given function on every triangle in the undirected graph exactly once
 *
 * @time O(n + m ^ (3/2))
 * @memory O(n + m)
 */
void enumerate_triangles(const vector<pair<int, int>>& edges, int n /*# of nodes*/, const function<void(int, int, int)>& f) {
	vector<int> deg(n);
	for (auto [u, v] : edges)
		deg[u]++, deg[v]++;
	vector<vector<int>> adj(n);
	for (auto [u, v] : edges) {
		if (tie(deg[u], u) > tie(deg[v], v))
			swap(u, v);
		adj[u].push_back(v);
	}
	vector<bool> seen(n);
	for (auto [u, v] : edges) {
		for (auto w : adj[u])
			seen[w] = 1;
		for (auto w : adj[v])
			if (seen[w])
				f(u, v, w);
		for (auto w : adj[u])
			seen[w] = 0;
	}
}
