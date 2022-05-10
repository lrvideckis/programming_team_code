#pragma once

//https://codeforces.com/blog/entry/74847
//assumes a single tree, 1-based nodes is possible by passing in `root` in range [1, n]
//status: all functions tested on random trees. `getLca` also tested on https://judge.yosupo.jp/problem/lca

struct lca {
	struct Node {
		int depth, jump, par;
		long long dist;
	};
	vector<Node> info;

	lca(const vector<vector<pair<int, long long>>>& adj, int root) : info(adj.size()) {
		info[root] = {
			0,
			root,
			root,
			0
		};
		dfs(root, -1, adj);
	}

	void dfs(int node, int par, const vector<vector<pair<int, long long>>>& adj) {
		for (auto [to, w] : adj[node]) {
			if (to == par) continue;
			int par2 = info[node].jump;
			info[to] = {
				info[node].depth + 1,
				info[node].depth - info[par2].depth == info[par2].depth - info[info[par2].jump].depth ? info[par2].jump : node,
				node,
				info[node].dist + w
			};
			dfs(to, node, adj);
		}
	}

	//traverse up k edges in O(log(k)). So with k=1 this returns `node`'s parent
	int kthPar(int node, int k) const {
		k = min(k, info[node].depth);
		while (k > 0) {
			int jumpDistEdges = info[node].depth - info[info[node].jump].depth;
			if (jumpDistEdges <= k) {
				k -= jumpDistEdges;
				node = info[node].jump;
			} else {
				k--;
				node = info[node].par;
			}
		}
		return node;
	}

	int getLca(int x, int y) const {
		if (info[x].depth < info[y].depth) swap(x, y);
		x = kthPar(x, info[x].depth - info[y].depth);
		while (x != y) {
			if (info[x].jump == info[y].jump)
				x = info[x].par, y = info[y].par;
			else
				x = info[x].jump, y = info[y].jump;
		}
		return x;
	}

	int distEdges(int x, int y) const {
		return info[x].depth + info[y].depth - 2 * info[getLca(x, y)].depth;
	}

	long long distWeight(int x, int y) const {
		return info[x].dist + info[y].dist - 2 * info[getLca(x, y)].dist;
	}
};
