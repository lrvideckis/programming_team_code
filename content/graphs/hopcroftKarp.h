#pragma once

//Modified from https://github.com/foreverbell/acm-icpc-cheat-sheet/blob/master/src/graph-algorithm/hopcroft-karp.cpp
//Worst case Ω(V^2) but fast in practice
//status: tested on https://judge.yosupo.jp/problem/bipartitematching with asserts checking correctness of min vertex cover

struct match {
	//edges in matching, given as array of std::pair(leftNode, rightNode)
	//size of matching = size of min vertex cover by König's theorem
	vector<pair<int,int>> matching;
	//an arbitrary min vertex cover is found. For this MVC: leftMVC[`left node`] is true iff `left node` is in the min vertex cover (same for rightMVC)
	//if leftMVC[`left node`] is false, then `left node` is in the corresponding maximal independent set
	vector<bool> leftMVC, rightMVC;
};

//Think of the bipartite graph as having a left side (with size lSz) and a right side (with size rSz).
//Nodes on left side are indexed 0,1,...,lSz-1
//Nodes on right side are indexed 0,1,...,rSz-1
//
//To initialize `adj`: For every edge nodeLeft <=> nodeRight, do: adj[nodeLeft].push_back(nodeRight)
match hopcroftKarp(const vector<vector<int>>& adj /*bipartite graph*/, const int m /*size of right side*/) {
	const int n = adj.size();
	vector<int> level(n), ml(n, -1), mr(m, -1);
	vector<bool> vis(n, false);

	while (true) {
		queue<int> q;
		for (int i = 0; i < n; i++) {
			if (ml[i] == -1) level[i] = 0, q.push(i);
			else level[i] = -1;
		}
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int x: adj[u]) {
				int v = mr[x];
				if (v != -1 && level[v] < 0) {
					level[v] = level[u] + 1;
					q.push(v);
				}
			}
		}
		for (int i = 0; i < n; i++) vis[i] = false;
		bool found = false;

		auto dfs = [&](auto&& dfs, int u) -> bool {
			vis[u] = true;
			for (int x : adj[u]) {
				int v = mr[x];
				if (v == -1 || (!vis[v] && level[u] < level[v] && dfs(dfs, v))) {
					ml[u] = x; mr[x] = u;
					return true;
				}
			}
			return false;
		};

		for (int i = 0; i < n; i++) if (ml[i] == -1 && dfs(dfs, i)) found = true;
		if (!found) break;
	}

	vector<pair<int,int>> matching;
	for(int i = 0; i < n; i++)
		if(ml[i] != -1)
			matching.push_back({i, ml[i]});

	//find min vertex cover
	vector<bool> visL(n, true), visR(m, false);
	auto dfs = [&](auto&& dfs, int node) -> void {
		visL[node] = false;
		for(auto to : adj[node]) {
			if(!visR[to] && mr[to] != -1) {
				visR[to] = true;
				dfs(dfs, mr[to]);
			}
		}
	};

	for(int i = 0; i < n; i++)
		if(ml[i] == -1)
			dfs(dfs, i);

	return {matching, visL, visR};
}
