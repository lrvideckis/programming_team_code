#pragma once
//library checker tests: https://judge.yosupo.jp/problem/scc

struct sccInfo {
	int numSCCs;
	//scc's are labeled 0,1,...,`numSCCs-1`
	//sccId[i] is the id of the scc containing node `i`
	vector<int> sccId;
};

sccInfo getSCCs(const vector<vector<int>>& adj /*directed, unweighted graph*/) {
	const int n = adj.size();
	stack<int> seen;
	{
		vector<bool> vis(n, false);
		auto dfs = [&](auto&& dfsPtr, int curr) -> void {
			if (vis[curr]) return;
			vis[curr] = true;
			for (int x : adj[curr]) dfsPtr(dfsPtr, x);
			seen.push(curr);
		};
		for (int i = 0; i < n; i++) dfs(dfs, i);
	}
	vector<vector<int>> adjInv(n);
	for (int i = 0; i < n; i++) {
		for (int to : adj[i])
			adjInv[to].push_back(i);
	}
	int numSCCs = 0;
	vector<int> sccId(n, -1);
	auto dfs = [&](auto&& dfsPtr, int curr) -> void {
		sccId[curr] = numSCCs;
		for (int x : adjInv[curr]) {
			if (sccId[x] == -1)
				dfsPtr(dfsPtr, x);
		}
	};
	while (!seen.empty()) {
		int node = seen.top();
		seen.pop();
		if (sccId[node] == -1) {
			dfs(dfs, node);
			numSCCs++;
		}
	}
	return {numSCCs, sccId};
}
