#pragma once
//source: https://codeforces.com/blog/entry/53170
//assumes a single tree, 1-based nodes is possible by passing in `root` in range [1, n]
//mnemonic: Heavy Light Decomposition
//NOLINTNEXTLINE(readability-identifier-naming)
struct HLD {
	struct node {
		int sub_sz, par, time_in, next;
	};
	vector<node> tree;
	HLD(vector<vector<int>>& adj /*single unrooted tree*/, int root) : tree(ssize(adj), {
		1, root, ssize(adj), root
	}) {
		dfs1(root, adj);
		int timer = 0;
		dfs2(root, adj, timer);
	}
	void dfs1(int v, vector<vector<int>>& adj) {
		for (int& to : adj[v]) {
			if (to == tree[v].par) continue;
			tree[to].par = v;
			dfs1(to, adj);
			tree[v].sub_sz += tree[to].sub_sz;
			if (tree[to].sub_sz > tree[adj[v][0]].sub_sz || adj[v][0] == tree[v].par)
				swap(to, adj[v][0]);
		}
	}
	void dfs2(int v, const vector<vector<int>>& adj, int& timer) {
		tree[v].time_in = timer++;
		for (int to : adj[v]) {
			if (to == tree[v].par) continue;
			tree[to].next = (timer == tree[v].time_in + 1 ? tree[v].next : to);
			dfs2(to, adj, timer);
		}
	}
	// Returns inclusive-exclusive intervals (of time_in's) corresponding to the path between u and v, not necessarily in order
	// This can answer queries for "is some node `x` on some path" by checking if the tree[x].time_in is in any of these intervals
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
	int lca(int u, int v) const {
		for (;; v = tree[tree[v].next].par) {
			if (tree[v].time_in < tree[u].time_in) swap(u, v);
			if (tree[tree[v].next].time_in <= tree[u].time_in) return u;
		}
	}
};
