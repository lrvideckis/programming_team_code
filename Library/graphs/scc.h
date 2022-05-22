#pragma once

//status: tested on https://judge.yosupo.jp/problem/scc
//building of condensation graph tested on https://cses.fi/problemset/task/1686/

struct sccInfo {
	int numSCCs;
	//scc's are labeled 0,1,...,`numSCCs-1`
	//sccId[i] is the id of the scc containing node `i`
	vector<int> sccId;
};

sccInfo getSCCs(const vector<vector<int>>& adj /*directed, unweighted graph*/) {
	int n = adj.size(), numSCCs = 0;
	stack<int> seen;
	{
		vector<bool> vis(n, false);
		auto dfs = [&](auto&& dfsPtr, int curr) -> void {
			vis[curr] = true;
			for (int x : adj[curr]) {
				if (!vis[x])
					dfsPtr(dfsPtr, x);
			}
			seen.push(curr);
		};
		for (int i = 0; i < n; ++i) {
			if (!vis[i])
				dfs(dfs, i);
		}
	}
	vector<vector<int>> adjInv(n);
	for (int i = 0; i < n; ++i) {
		for (int to : adj[i])
			adjInv[to].push_back(i);
	}
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
