#pragma once
//library checker tests: https://judge.yosupo.jp/problem/lca
//https://codeforces.com/blog/entry/74847
//assumes a single tree, 1-based nodes is possible by passing in `root` in range [1, n]
struct LCA {
	int n;
	vector<int> jmp, jmp_edges, par, depth;
	vector<long long> dist;
	LCA(const vector<vector<pair<int, long long>>>& adj, int root) :
		n(adj.size()), jmp(n, root), jmp_edges(n, 1), par(n, root), depth(n, 0), dist(n, 0LL) {
		dfs(root, adj);
	}
	void dfs(int node, const vector<vector<pair<int, long long>>>& adj) {
		for (auto [ch, w] : adj[node]) {
			if (ch == par[node]) continue;
			par[ch] = node;
			depth[ch] = 1 + depth[node];
			dist[ch] = w + dist[node];
			if (depth[node] > 0 && jmp_edges[node] == jmp_edges[jmp[node]])
				jmp[ch] = jmp[jmp[node]], jmp_edges[ch] = 2 * jmp_edges[node] + 1;
			else
				jmp[ch] = node;
			dfs(ch, adj);
		}
	}
	//traverse up k edges in O(log(k)). So with k=1 this returns `node`'s parent
	int kth_par(int node, int k) const {
		k = min(k, depth[node]);
		while (k > 0) {
			if (jmp_edges[node] <= k) {
				k -= jmp_edges[node];
				node = jmp[node];
			} else {
				k--;
				node = par[node];
			}
		}
		return node;
	}
	int get_lca(int x, int y) const {
		if (depth[x] < depth[y]) swap(x, y);
		x = kth_par(x, depth[x] - depth[y]);
		while (x != y) {
			if (jmp[x] != jmp[y])
				x = jmp[x], y = jmp[y];
			else
				x = par[x], y = par[y];
		}
		return x;
	}
	int dist_edges(int x, int y) const {
		return depth[x] + depth[y] - 2 * depth[get_lca(x, y)];
	}
	long long dist_weight(int x, int y) const {
		return dist[x] + dist[y] - 2 * dist[get_lca(x, y)];
	}
};
