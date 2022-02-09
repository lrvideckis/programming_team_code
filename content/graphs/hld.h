#pragma once

//status: all functions tested on random trees; also `lca` tested on https://judge.yosupo.jp/problem/lca

struct hld {
	vector<int> Size, par, Depth, timeIn, Next, timeInToNode;
	hld(vector<vector<int>>& adj /*forest of trees*/, int root = -1/*pass in to specify root, usually for a single component*/) :
		Size(adj.size(),1), par(adj.size(),-1), Depth(adj.size(),1), timeIn(adj.size()), Next(adj.size(),-1), timeInToNode(adj.size()) {
		int Time=0;
		auto callDfss = [&](int node) -> void {
			Next[node] = par[node] = node;
			dfs1(node,adj);
			dfs2(node,adj,Time);
		};
		if(root != -1)
			callDfss(root);
		for(int i = 0; i < (int)adj.size(); i++) {
			if(par[i] == -1)  //roots each tree by node with min label
				callDfss(i);
		}
	}
	void dfs1(int node, vector<vector<int>>& adj) {
		for(auto& to: adj[node]) {
			if(to == par[node]) continue;
			Depth[to] = 1 + Depth[node];
			par[to] = node;
			dfs1(to, adj);
			Size[node] += Size[to];
			if(Size[to] > Size[adj[node][0]] || adj[node][0] == par[node])
				swap(to, adj[node][0]);
		}
	}
	void dfs2(int node, const vector<vector<int>>& adj, int& Time) {
		timeIn[node] = Time;
		timeInToNode[Time] = node;
		Time++;
		for(auto to: adj[node]) {
			if(to == par[node]) continue;
			Next[to] = (Time == timeIn[node]+1 ? Next[node] : to);
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
	pair<int,int> subtree(int i) const {
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
