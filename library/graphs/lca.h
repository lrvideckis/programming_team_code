#pragma once
//https://codeforces.com/blog/entry/74847
//assumes a single tree, 1-based nodes is possible by passing in `root` in range [1, n]
//mnemonic: Least/Lowest Common Ancestor
//NOLINTNEXTLINE(readability-identifier-naming)
struct LCA {
	struct node {
		int jmp, jmp_edges, par, depth;
		long long dist;
	};
	vector<node> tree;
	LCA(const vector<vector<pair<int, long long>>>& adj, int root) : tree(adj.size(), {
		root, 1, root, 0, 0LL
	}) {
		dfs(root, adj);
	}
	void dfs(int v, const vector<vector<pair<int, long long>>>& adj) {
		int jmp, jmp_edges;
		if (tree[v].depth > 0 && tree[v].jmp_edges == tree[tree[v].jmp].jmp_edges)
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
	//traverse up k edges in O(log(k)). So with k=1 this returns `v`'s parent
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
