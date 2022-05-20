#pragma once

//status: all functions tested on random trees; also `lca` tested on https://judge.yosupo.jp/problem/lca
//assumes a single tree, 1-based nodes is possible by passing in `root` in range [1, n]

struct hld {
	int n;
	vector<int> Size, par, timeIn, Next;
	hld(vector<vector<int>>& adj /*single unrooted tree*/, int root) :
		n(adj.size()), Size(n, 1), par(n, root), timeIn(n), Next(n, root) {
		dfs1(root, adj);
		int Time = 0;
		dfs2(root, adj, Time);
	}
	void dfs1(int node, vector<vector<int>>& adj) {
		for (auto& to : adj[node]) {
			if (to == par[node]) continue;
			par[to] = node;
			dfs1(to, adj);
			Size[node] += Size[to];
			if (Size[to] > Size[adj[node][0]] || adj[node][0] == par[node])
				swap(to, adj[node][0]);
		}
	}
	void dfs2(int node, const vector<vector<int>>& adj, int& Time) {
		timeIn[node] = Time;
		Time++;
		for (auto to : adj[node]) {
			if (to == par[node]) continue;
			Next[to] = (Time == timeIn[node] + 1 ? Next[node] : to);
			dfs2(to, adj, Time);
		}
	}
	// Returns intervals (of timeIn's) corresponding to the path between u and v, not necessarily in order
	// This can answer queries for "is some node `x` on some path" by checking if the timeIn[x] is in any of these intervals
	vector<pair<int, int>> path(int u, int v) const {
		vector<pair<int, int>> res;
		for (;; v = par[Next[v]]) {
			if (timeIn[v] < timeIn[u]) swap(u, v);
			if (timeIn[Next[v]] <= timeIn[u]) {
				res.push_back({timeIn[u], timeIn[v]});
				return res;
			}
			res.push_back({timeIn[Next[v]], timeIn[v]});
		}
	}
	// Returns interval (of timeIn's) corresponding to the subtree of node i
	// This can answer queries for "is some node `x` in some other node's subtree" by checking if timeIn[x] is in this interval
	pair<int, int> subtree(int i) const {
		return {timeIn[i], timeIn[i] + Size[i] - 1};
	}
	// Returns lca of nodes u and v
	int lca(int u, int v) const {
		for (;; v = par[Next[v]]) {
			if (timeIn[v] < timeIn[u]) swap(u, v);
			if (timeIn[Next[v]] <= timeIn[u]) return u;
		}
	}
};
