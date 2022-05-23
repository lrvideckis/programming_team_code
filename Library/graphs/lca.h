#pragma once

//https://codeforces.com/blog/entry/74847
//assumes a single tree, 1-based nodes is possible by passing in `root` in range [1, n]
//status: all functions tested on random trees. `getLca` also tested on https://judge.yosupo.jp/problem/lca

struct lca {
	int n;
	vector<int> jmp, jmpEdges, par, depth;
	vector<long long> dist;

	lca(const vector<vector<pair<int, long long>>>& adj, int root) :
		n(adj.size()), jmp(n, root), jmpEdges(n, 0), par(n, root), depth(n, 0), dist(n, 0LL) {
		dfs(root, adj);
	}

	void dfs(int node, const vector<vector<pair<int, long long>>>& adj) {
		for (auto [ch, w] : adj[node]) {
			if (ch == par[node]) continue;
			par[ch] = node;
			depth[ch] = 1 + depth[node];
			dist[ch] = w + dist[node];
			if (jmpEdges[node] > 0 && jmpEdges[node] == jmpEdges[jmp[node]])
				jmp[ch] = jmp[jmp[node]], jmpEdges[ch] = 2 * jmpEdges[node] + 1;
			else
				jmp[ch] = node, jmpEdges[ch] = 1;
			dfs(ch, adj);
		}
	}

	//traverse up k edges in O(log(k)). So with k=1 this returns `node`'s parent
	int kthPar(int node, int k) const {
		k = min(k, depth[node]);
		while (k > 0) {
			if (jmpEdges[node] <= k) {
				k -= jmpEdges[node];
				node = jmp[node];
			} else {
				k--;
				node = par[node];
			}
		}
		return node;
	}

	int getLca(int x, int y) const {
		if (depth[x] < depth[y]) swap(x, y);
		x = kthPar(x, depth[x] - depth[y]);
		while (x != y) {
			if (jmp[x] != jmp[y])
				x = jmp[x], y = jmp[y];
			else
				x = par[x], y = par[y];
		}
		return x;
	}

	int distEdges(int x, int y) const {
		return depth[x] + depth[y] - 2 * depth[getLca(x, y)];
	}

	long long distWeight(int x, int y) const {
		return dist[x] + dist[y] - 2 * dist[getLca(x, y)];
	}
};
