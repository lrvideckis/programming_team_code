/** @file */
#pragma once
/**
 * @author lightseba
 * @see https://github.com/ucf-programming-team/hackpack-cpp/blob/master/content/graphs/TreeLifting.h
 * Calculate jumps up a tree, to support fast upward jumps and LCAs.
 */
struct lift {
	vector<int> d, p, j;
	lift(const vector<vector<int>>& adj): d(ssize(adj)), p(d), j(d) {
		dfs(0, adj);
	}
	void dfs(int u, vector<vi>& adj) {
		int jmp = (d[u] + d[j[j[u]]] == 2 * d[j[u]]) ? j[j[u]] : u;
		for (int v : adj[u])
			if (v != p[u])
				d[v] = d[p[v] = u] + 1, j[v] = jmp, dfs(v, adj);
	}
	int lca(int u, int v) const {
		if (d[u] < d[v]) swap(u, v);
		while (d[u] > d[v]) u = d[j[u]] >= d[v] ? j[u] : p[u];
		if (u == v) return u;
		while (p[u] != p[v])
			if (j[u] != j[v]) u = j[u], v = j[v];
			else u = p[u], v = p[v];
		return p[u];
	}
	int kth(int u, int k) const {
		if (k > d[u]) return -1;
		k = d[u] - k;
		while (d[u] > k) u = d[j[u]] >= k ? j[u] : p[u];
		return u;
	}
	int kth_path(int u, int v, int k) const {
	}
};
