#pragma once
//library checker tests: https://judge.yosupo.jp/problem/bipartitematching
//with asserts checking correctness of min vertex cover
//Modified from https://github.com/foreverbell/acm-icpc-cheat-sheet/blob/master/src/graph-algorithm/hopcroft-karp.cpp
//Worst case O(E*sqrt(V)) but faster in practice
struct match {
	//# of edges in matching (which = size of min vertex cover by König's theorem)
	int size_of_matching;
	//an arbitrary max matching is found. For this matching:
	//if match_l[node_left] == -1:
	//    `node_left` is not in matching
	//else:
	//    the edge `node_left` <=> match_l[node_left] is in the matching
	//
	//similarly for match_r with edge match_r[node_right] <=> node_right in matching if match_r[node_right] != -1
	//matchings stored in match_l and match_r are the same matching
	//provides way to check if any node is in matching
	vector<int> match_l, match_r;
	//an arbitrary min vertex cover is found. For this MVC: mvc_l[`left node`] is true iff `left node` is in the min vertex cover (same for mvc_r)
	//if mvc_l[`left node`] is false, then `left node` is in the corresponding maximal independent set
	vector<bool> mvc_l, mvc_r;
};
//Think of the bipartite graph as having a left side (with size lsz) and a right side (with size rsz).
//Nodes on left side are indexed 0,1,...,lsz-1
//Nodes on right side are indexed 0,1,...,rsz-1
//
//`adj` is like a directed adjacency list containing edges from left side -> right side:
//To initialize `adj`: For every edge node_left <=> node_right, do: adj[node_left].push_back(node_right)
match hopcroft_karp(const vector<vector<int>>& adj/*bipartite graph*/, int rsz/*number of nodes on right side*/) {
	int size_of_matching = 0, lsz = adj.size();
	vector<int> match_l(lsz, -1), match_r(rsz, -1);
	while (true) {
		queue<int> q;
		vector<int> level(lsz, -1);
		for (int i = 0; i < lsz; i++) {
			if (match_l[i] == -1) level[i] = 0, q.push(i);
		}
		bool found = false;
		vector<bool> mvc_l(lsz, true), mvc_r(rsz, false);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			mvc_l[u] = false;
			for (int x : adj[u]) {
				mvc_r[x] = true;
				int v = match_r[x];
				found |= v == -1;
				if (v != -1 && level[v] < 0) {
					level[v] = level[u] + 1;
					q.push(v);
				}
			}
		}
		if (!found) return {size_of_matching, match_l, match_r, mvc_l, mvc_r};
		auto dfs = [&](auto self, int u) -> bool {
			for (int x : adj[u]) {
				int v = match_r[x];
				if (v == -1 || (level[u] + 1 == level[v] && self(self, v))) {
					match_l[u] = x;
					match_r[x] = u;
					return true;
				}
			}
			level[u] = 1e9; //acts as visited array
			return false;
		};
		for (int i = 0; i < lsz; i++)
			size_of_matching += (match_l[i] == -1 && dfs(dfs, i));
	}
}
