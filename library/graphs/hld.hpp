#pragma once
/**
 * @brief Heavy Light Decomposition
 * @see https://codeforces.com/blog/entry/53170
 */
//NOLINTNEXTLINE(readability-identifier-naming)
struct HLD {
	struct node {
		int sub_sz = 1, par = -1, time_in = -1, next = -1;
	};
	vector<node> tree;
	/**
	 * @time O(n)
	 * @memory O(n)
	 */
	HLD(vector<vector<int>>& adj/*forest of unrooted trees*/) : tree(ssize(adj)) {
		for (int i = 0, timer = 0; i < ssize(adj); i++) {
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
			tree[v].sub_sz += tree[to].sub_sz;
			if (tree[to].sub_sz > tree[adj[v][0]].sub_sz)
				swap(to, adj[v][0]);
		}
	}
	void dfs2(int v, const vector<vector<int>>& adj, int& timer) {
		tree[v].time_in = timer++;
		for (int to : adj[v]) {
			tree[to].next = (timer == tree[v].time_in + 1 ? tree[v].next : to);
			dfs2(to, adj, timer);
		}
	}
	/**
	 * @brief Returns inclusive-exclusive intervals (of time_in's)
	 *     corresponding to the path between u and v, not necessarily in order.
	 * @note u, v must be in the same component.
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
	pair<int, int> subtree(int i) const {
		return {tree[i].time_in, tree[i].time_in + tree[i].sub_sz};
	}
	/**
	 * @note u, v must be in the same component.
	 * @time O(log n)
	 */
	int lca(int u, int v) const {
		for (;; v = tree[tree[v].next].par) {
			if (tree[v].time_in < tree[u].time_in) swap(u, v);
			if (tree[tree[v].next].time_in <= tree[u].time_in) return u;
		}
	}
};
