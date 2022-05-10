#pragma once

//https://codeforces.com/blog/entry/74847
//status: all functions tested on random trees. `getLca` also tested on https://judge.yosupo.jp/problem/lca

struct lca {
	struct Node {
		int depth, jump, par, dist;
	};
	vector<Node> info;

	lca(const vector<vector<pair<int, long long>>>& adj, int root) :
		info(adj.size()) {
		dfs(root, root, 0, adj);
	}

	void dfs(int node, int par, int weightToPar, const vector<vector<pair<int, long long>>>& adj) {
		int par2 = info[par].jump;
		info[node] = {
			info[par].depth + 1,
			info[par].depth - info[par2].depth == info[par2].depth - info[info[par2].jump].depth ? info[par2].jump : par,
			par,
			info[par].dist + weightToPar
		};
		for (auto [to, w] : adj[node]) {
			if (to == par) continue;
			dfs(to, node, w, adj);
		}
	}

	int kthPar(int node, int k) const {
		while(k > 0 && node > 0) {
			if(info[node].depth - k <= info[info[node].jump].depth) {
				k -= info[node].depth - info[info[node].jump].depth;
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
		if (x == y) return x;
		while(x != y) {
			if(info[x].jump == info[y].jump) {
				x = info[x].par;
				y = info[y].par;
			} else {
				x = info[x].jump;
				y = info[y].jump;
			}
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
