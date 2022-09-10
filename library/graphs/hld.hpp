#pragma once
//source: https://codeforces.com/blog/entry/53170
//mnemonic: Heavy Light Decomposition
//NOLINTNEXTLINE(readability-identifier-naming)
struct HLD {
	struct node {
		int sub_sz = 1, par = -1, time_in = -1, next = -1;
	};
	vector<node> tree;
	HLD(vector<vector<int>>& adj/*forest of unrooted trees*/) : tree(adj.size()) {
		int timer = 0;
		for (int i = 0; i < (int)adj.size(); i++) {
			if (tree[i].next == -1) {//lowest indexed node in each tree becomes root
				tree[i].next = i;
				dfs1(i, adj);
				dfs2(i, adj, timer);
			}
		}
	}
	void dfs1(int v, vector<vector<int>>& adj) {
		auto par = find(adj[v].begin(), adj[v].end(), tree[v].par);
		if (par != adj[v].end()) adj[v].erase(par);
		for (int& to : adj[v]) {
			tree[to].par = v;
			dfs1(to, adj);
			if (tree[to].sub_sz > tree[adj[v][0]].sub_sz)
				swap(to, adj[v][0]);
			tree[v].sub_sz += tree[to].sub_sz;
		}
	}
	void dfs2(int v, const vector<vector<int>>& adj, int& timer) {
		tree[v].time_in = timer++;
		for (int to : adj[v]) {
			tree[to].next = (timer == tree[v].time_in + 1 ? tree[v].next : to);
			dfs2(to, adj, timer);
		}
	}
	// Returns inclusive-exclusive intervals (of time_in's) corresponding to the path between u and v, not necessarily in order
	// This can answer queries for "is some node `x` on some path" by checking if the tree[x].time_in is in any of these intervals
	// u, v must be in the same component
	vector<pair<int, int>> path(int u, int v) const {
		vector<pair<int, int>> res;
		for (;; v = tree[tree[v].next].par) {
			if (tree[v].time_in < tree[u].time_in) swap(u, v);
			if (tree[tree[v].next].time_in <= tree[u].time_in) {
				res.emplace_back(tree[u].time_in, tree[v].time_in + 1);
				return res;
			}
			res.emplace_back(tree[tree[v].next].time_in, tree[v].time_in + 1);
		}
	}
	// Returns interval (of time_in's) corresponding to the subtree of node i
	// This can answer queries for "is some node `x` in some other node's subtree" by checking if tree[x].time_in is in this interval
	pair<int, int> subtree(int i) const {
		return {tree[i].time_in, tree[i].time_in + tree[i].sub_sz};
	}
	// Returns lca of nodes u and v
	// u, v must be in the same component
	int lca(int u, int v) const {
		for (;; v = tree[tree[v].next].par) {
			if (tree[v].time_in < tree[u].time_in) swap(u, v);
			if (tree[tree[v].next].time_in <= tree[u].time_in) return u;
		}
	}
};
