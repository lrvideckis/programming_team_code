#pragma once
//library checker tests: https://judge.yosupo.jp/problem/lca, https://judge.yosupo.jp/problem/vertex_add_path_sum, https://judge.yosupo.jp/problem/vertex_add_subtree_sum
//source: https://codeforces.com/blog/entry/53170
//assumes a single tree, 1-based nodes is possible by passing in `root` in range [1, n]
//NOLINTNEXTLINE(readability-identifier-naming)
struct HLD {
	int n;
	vector<int> sub_sz, par, time_in, next;
	HLD(vector<vector<int>>& adj /*single unrooted tree*/, int root) :
		n(adj.size()), sub_sz(n, 1), par(n, root), time_in(n), next(n, root) {
		dfs1(root, adj);
		int timer = 0;
		dfs2(root, adj, timer);
	}
	void dfs1(int node, vector<vector<int>>& adj) {
		for (int& to : adj[node]) {
			if (to == par[node]) continue;
			par[to] = node;
			dfs1(to, adj);
			sub_sz[node] += sub_sz[to];
			if (sub_sz[to] > sub_sz[adj[node][0]] || adj[node][0] == par[node])
				swap(to, adj[node][0]);
		}
	}
	void dfs2(int node, const vector<vector<int>>& adj, int& timer) {
		time_in[node] = timer++;
		for (int to : adj[node]) {
			if (to == par[node]) continue;
			next[to] = (timer == time_in[node] + 1 ? next[node] : to);
			dfs2(to, adj, timer);
		}
	}
	// Returns intervals (of time_in's) corresponding to the path between u and v, not necessarily in order
	// This can answer queries for "is some node `x` on some path" by checking if the time_in[x] is in any of these intervals
	vector<pair<int, int>> path(int u, int v) const {
		vector<pair<int, int>> res;
		for (;; v = par[next[v]]) {
			if (time_in[v] < time_in[u]) swap(u, v);
			if (time_in[next[v]] <= time_in[u]) {
				res.emplace_back(time_in[u], time_in[v]);
				return res;
			}
			res.emplace_back(time_in[next[v]], time_in[v]);
		}
	}
	// Returns interval (of time_in's) corresponding to the subtree of node i
	// This can answer queries for "is some node `x` in some other node's subtree" by checking if time_in[x] is in this interval
	pair<int, int> subtree(int i) const {
		return {time_in[i], time_in[i] + sub_sz[i] - 1};
	}
	// Returns lca of nodes u and v
	int lca(int u, int v) const {
		for (;; v = par[next[v]]) {
			if (time_in[v] < time_in[u]) swap(u, v);
			if (time_in[next[v]] <= time_in[u]) return u;
		}
	}
};
