#pragma once
//library checker tests: https://judge.yosupo.jp/problem/bipartitematching
//with asserts checking correctness of min vertex cover

//Modified from https://github.com/foreverbell/acm-icpc-cheat-sheet/blob/master/src/graph-algorithm/hopcroft-karp.cpp
//Worst case O(E*sqrt(V)) but faster in practice

struct match {
	//# of edges in matching (which = size of min vertex cover by König's theorem)
	int sizeOfMatching;
	//an arbitrary max matching is found. For this matching:
	//if ml[nodeLeft] == -1:
	//    `nodeLeft` is not in matching
	//else:
	//    the edge `nodeLeft` <=> ml[nodeLeft] is in the matching
	//
	//similarly for mr with edge mr[nodeRight] <=> nodeRight in matching if mr[nodeRight] != -1
	//matchings stored in ml and mr are the same matching
	//provides way to check if any node is in matching
	vector<int> ml, mr;
	//an arbitrary min vertex cover is found. For this MVC: leftMVC[`left node`] is true iff `left node` is in the min vertex cover (same for rightMVC)
	//if leftMVC[`left node`] is false, then `left node` is in the corresponding maximal independent set
	vector<bool> leftMVC, rightMVC;
};

//Think of the bipartite graph as having a left side (with size lSz) and a right side (with size rSz).
//Nodes on left side are indexed 0,1,...,lSz-1
//Nodes on right side are indexed 0,1,...,rSz-1
//
//`adj` is like a directed adjacency list containing edges from left side -> right side:
//To initialize `adj`: For every edge nodeLeft <=> nodeRight, do: adj[nodeLeft].push_back(nodeRight)
match hopcroftKarp(const vector<vector<int>>& adj/*bipartite graph*/, int rSz/*number of nodes on right side*/) {
	int sizeOfMatching = 0, lSz = adj.size();
	vector<int> ml(lSz, -1), mr(rSz, -1);
	while (true) {
		queue<int> q;
		vector<int> level(lSz, -1);
		for (int i = 0; i < lSz; i++) {
			if (ml[i] == -1) level[i] = 0, q.push(i);
		}
		bool found = false;
		vector<bool> leftMVC(lSz, true), rightMVC(rSz, false);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			leftMVC[u] = false;
			for (int x : adj[u]) {
				rightMVC[x] = true;
				int v = mr[x];
				found |= v == -1;
				if (v != -1 && level[v] < 0) {
					level[v] = level[u] + 1;
					q.push(v);
				}
			}
		}
		if (!found) return {sizeOfMatching, ml, mr, leftMVC, rightMVC};
		auto dfs = [&](auto self, int u) -> bool {
			for (int x : adj[u]) {
				int v = mr[x];
				if (v == -1 || (level[u] + 1 == level[v] && self(self, v))) {
					ml[u] = x;
					mr[x] = u;
					return true;
				}
			}
			level[u] = 1e9; //acts as visited array
			return false;
		};
		for (int i = 0; i < lSz; i++)
			sizeOfMatching += (ml[i] == -1 && dfs(dfs, i));
	}
}
