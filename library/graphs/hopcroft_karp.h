#pragma once
//library checker tests: https://judge.yosupo.jp/problem/bipartitematching
//with asserts checking correctness of min vertex cover
//Modified from https://github.com/foreverbell/acm-icpc-cheat-sheet/blob/master/src/graph-algorithm/hopcroft-karp.cpp
//Worst case O(E*sqrt(V)) but faster in practice
struct match {
	//# of edges in matching (which = size of min vertex cover by König's theorem)
	int size_of_matching;
	//an arbitrary max matching is found. For this matching:
	//if match_l[nodeLeft] == -1:
	//    `nodeLeft` is not in matching
	//else:
	//    the edge `nodeLeft` <=> match_l[nodeLeft] is in the matching
	//
	//similarly for match_r with edge match_r[nodeRight] <=> nodeRight in matching if match_r[nodeRight] != -1
	//matchings stored in match_l and match_r are the same matching
	//provides way to check if any node is in matching
	vector<int> match_l, match_r;
	//an arbitrary min vertex cover is found. For this MVC: mvc_l[`left node`] is true iff `left node` is in the min vertex cover (same for mvc_r)
	//if mvc_l[`left node`] is false, then `left node` is in the corresponding maximal independent set
	vector<bool> mvc_l, mvc_r;
};
//Think of the bipartite graph as having a left side (with size l_sz) and a right side (with size r_sz).
//Nodes on left side are indexed 0,1,...,l_sz-1
//Nodes on right side are indexed 0,1,...,r_sz-1
//
//`adj` is like a directed adjacency list containing edges from left side -> right side:
//To initialize `adj`: For every edge nodeLeft <=> nodeRight, do: adj[nodeLeft].push_back(nodeRight)
match hopcroft_karp(const vector<vector<int>>& adj/*bipartite graph*/, int r_sz/*number of nodes on right side*/) {
	int size_of_matching = 0, l_sz = adj.size();
	vector<int> match_l(l_sz, -1), match_r(r_sz, -1);
	while (true) {
		queue<int> q;
		vector<int> level(l_sz, -1);
		for (int i = 0; i < l_sz; i++) {
			if (match_l[i] == -1) level[i] = 0, q.push(i);
		}
		bool found = false;
		vector<bool> mvc_l(l_sz, true), mvc_r(r_sz, false);
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
		for (int i = 0; i < l_sz; i++)
			size_of_matching += (match_l[i] == -1 && dfs(dfs, i));
	}
}
