#pragma once
/**
 * @brief Least/Lowest Common Ancestor
 * @see https://codeforces.com/blog/entry/74847
 */
//NOLINTNEXTLINE(readability-identifier-naming)
struct LCA {
	struct node {
		int jmp = -1, jmp_edges = 0, par = -1, depth = 0;
		long long dist = 0LL;
	};
	vector<node> tree;
	/**
	 * @time O(n)
	 * @memory O(n)
	 */
	LCA(const vector<vector<pair<int, long long>>>& adj/*forest of weighted trees*/) : tree(ssize(adj)) {
		for (int i = 0; i < ssize(adj); i++) {
			if (tree[i].jmp == -1) {//lowest indexed node in each tree becomes root
				tree[i].jmp = i;
				dfs(i, adj);
			}
		}
	}
	void dfs(int v, const vector<vector<pair<int, long long>>>& adj) {
		int jmp, jmp_edges;
		if (tree[v].jmp != v && tree[v].jmp_edges == tree[tree[v].jmp].jmp_edges)
			jmp = tree[tree[v].jmp].jmp, jmp_edges = 2 * tree[v].jmp_edges + 1;
		else
			jmp = v, jmp_edges = 1;
		for (auto [ch, w] : adj[v]) {
			if (ch == tree[v].par) continue;
			tree[ch] = {
				jmp,
				jmp_edges,
				v,
				1 + tree[v].depth,
				w + tree[v].dist
			};
			dfs(ch, adj);
		}
	}
	/**
	 * @brief Traverse up k edges. So with k=1 this returns v's parent.
	 * @time O(log k)
	 */
	int kth_par(int v, int k) const {
		k = min(k, tree[v].depth);
		while (k > 0) {
			if (tree[v].jmp_edges <= k) {
				k -= tree[v].jmp_edges;
				v = tree[v].jmp;
			} else {
				k--;
				v = tree[v].par;
			}
		}
		return v;
	}
	/**
	 * @note x, y must be in the same component.
	 * @time O(log n)
	 */
	int get_lca(int x, int y) const {
		if (tree[x].depth < tree[y].depth) swap(x, y);
		x = kth_par(x, tree[x].depth - tree[y].depth);
		while (x != y) {
			if (tree[x].jmp != tree[y].jmp)
				x = tree[x].jmp, y = tree[y].jmp;
			else
				x = tree[x].par, y = tree[y].par;
		}
		return x;
	}
	int dist_edges(int x, int y) const {
		return tree[x].depth + tree[y].depth - 2 * tree[get_lca(x, y)].depth;
	}
	long long dist_weight(int x, int y) const {
		return tree[x].dist + tree[y].dist - 2 * tree[get_lca(x, y)].dist;
	}
};
