#pragma once
//library checker tests: https://judge.yosupo.jp/problem/bipartitematching
//with asserts checking correctness of min vertex cover
//source: https://github.com/foreverbell/acm-icpc-cheat-sheet/blob/master/src/graph-algorithm/hopcroft-karp.cpp
//Worst case O(E*sqrt(V)) but faster in practice
struct match {
	//# of edges in matching (which = size of min vertex cover by König's theorem)
	int size_of_matching;
	//an arbitrary max matching is found. For this matching:
	//if l_to_r[node_left] == -1:
	//	node_left is not in matching
	//else:
	//	the edge `node_left` <=> l_to_r[node_left] is in the matching
	//
	//similarly for r_to_l with edge r_to_l[node_right] <=> node_right in matching if r_to_l[node_right] != -1
	//matchings stored in l_to_r and r_to_l are the same matching
	//provides way to check if any node/edge is in matching
	vector<int> l_to_r, r_to_l;
	//an arbitrary min vertex cover is found. For this mvc: mvc_l[node_left] is true iff node_left is in the min vertex cover (same for mvc_r)
	//if mvc_l[node_left] is false, then node_left is in the corresponding maximal independent set
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
	vector<int> l_to_r(lsz, -1), r_to_l(rsz, -1);
	while (true) {
		queue<int> q;
		vector<int> level(lsz, -1);
		for (int i = 0; i < lsz; i++) {
			if (l_to_r[i] == -1) level[i] = 0, q.push(i);
		}
		bool found = false;
		vector<bool> mvc_l(lsz, true), mvc_r(rsz, false);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			mvc_l[u] = false;
			for (int x : adj[u]) {
				mvc_r[x] = true;
				int v = r_to_l[x];
				if (v == -1) found = true;
				else if (level[v] == -1) {
					level[v] = level[u] + 1;
					q.push(v);
				}
			}
		}
		if (!found) return {size_of_matching, l_to_r, r_to_l, mvc_l, mvc_r};
		auto dfs = [&](auto self, int u) -> bool {
			for (int x : adj[u]) {
				int v = r_to_l[x];
				if (v == -1 || (level[u] + 1 == level[v] && self(self, v))) {
					l_to_r[u] = x;
					r_to_l[x] = u;
					return true;
				}
			}
			level[u] = 1e9; //acts as visited array
			return false;
		};
		for (int i = 0; i < lsz; i++)
			size_of_matching += (l_to_r[i] == -1 && dfs(dfs, i));
	}
}
