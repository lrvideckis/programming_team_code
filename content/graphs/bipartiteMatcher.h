#pragma once

//Implementation of Hopcroft-Karp algorithm
//O(m * sqrt(n)) where n = # nodes, m = # edges
//status: tested on https://judge.yosupo.jp/problem/bipartitematching with asserts checking correctness of min vertex cover

struct match {
	//edges in matching. size of matching = size of min vertex cover by König's theorem
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
match bipartiteMatcher(const vector<vector<int>>& adj /*bipartite graph*/, const int rSz /*size of right side*/) {
	const int lSz = adj.size();
	vector<int> L(lSz, -1), R(rSz, -1);
	vector<bool> visL(lSz), visR(rSz);

	auto Match = [&](auto&& Match, int node) -> bool {
		if(visL[node]) return false;
		visL[node] = true;
		for(int vec : adj[node]) {
			if(R[vec] == -1 || Match(Match, R[vec])) {
				L[node] = vec;
				R[vec] = node;
				return true;
			}
		}
		return false;
	};

	bool ok = true;
	while(ok) {
		ok = false;
		fill(visL.begin(), visL.end(), 0);
		for(int i = 0; i < lSz; i++)
			if(L[i] == -1 && Match(Match, i))
				ok = true;
	}

	vector<pair<int,int>> matching;
	for(int i = 0; i < lSz; i++)
		if(L[i] != -1)
			matching.push_back({i, L[i]});

	//find min vertex cover
	auto dfs = [&](auto&& dfs, int node) -> void {
		visL[node] = false;
		for(auto to : adj[node]) {
			if(!visR[to] && R[to] != -1) {
				visR[to] = true;
				dfs(dfs, R[to]);
			}
		}
	};

	fill(visL.begin(), visL.end(), true);
	fill(visR.begin(), visR.end(), false);
	for(int i = 0; i < lSz; i++)
		if(L[i] == -1)
			dfs(dfs, i);
	return {matching, visL, visR};
}
