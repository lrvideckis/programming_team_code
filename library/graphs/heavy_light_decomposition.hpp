/** @file */
#pragma once
/**
 * @see https://codeforces.com/blog/entry/53170
 */
//NOLINTNEXTLINE(readability-identifier-naming)
struct HLD {
	struct node {
		int sub_sz = 1, par = -1, time_in = -1, next = -1;
	};
	vector<node> tree;
	/**
	 * @param adj forest of unrooted trees
	 * @time O(n)
	 * @memory O(n)
	 */
	HLD(vector<vector<int>>& adj) : tree(ssize(adj)) {
		for (int i = 0, timer = 0; i < ssize(adj); i++) {
			if (tree[i].next == -1) {
				tree[i].next = i;
				dfs1(i, adj);
				dfs2(i, adj, timer);
			}
		}
	}
	void dfs1(int v, vector<vector<int>>& adj) {
		for (auto& to : adj[v]) {
			adj[to].erase(find(adj[to].begin(), adj[to].end(), v));
			tree[to].par = v;
			dfs1(to, adj);
			tree[v].sub_sz += tree[to].sub_sz;
			if (tree[to].sub_sz > tree[adj[v][0]].sub_sz)
				swap(to, adj[v][0]);
		}
	}
	void dfs2(int v, const vector<vector<int>>& adj, int& timer) {
		tree[v].time_in = timer++;
		for (auto to : adj[v]) {
			tree[to].next = (timer == tree[v].time_in + 1 ? tree[v].next : to);
			dfs2(to, adj, timer);
		}
	}
	/**
	 * @param u,v endpoint nodes of a path
	 * @returns vector of intervals [time_l, time_r) representing path u,v; not
	 * necessarily in order.
	 * @time O(log n)
	 * @memory O(log n)
	 */
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
	/**
	 * @param v a node
	 * @returns range [time_l, time_r) representing v's subtree
	 */
	pair<int, int> subtree(int v) const {
		return {tree[v].time_in, tree[v].time_in + tree[v].sub_sz};
	}
	/**
	 * @param u,v 2 nodes in the same component
	 * @returns lca of u, v
	 * @time O(log n)
	 * @memory O(1)
	 */
	int lca(int u, int v) const {
		for (;; v = tree[tree[v].next].par) {
			if (tree[v].time_in < tree[u].time_in) swap(u, v);
			if (tree[tree[v].next].time_in <= tree[u].time_in) return u;
		}
	}
};
