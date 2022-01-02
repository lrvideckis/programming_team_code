#pragma once

//usage:
//	auto [sccId, numSccs] = getSCCs(adj);
//where sccId[i] is the id of the scc containing node `i`
//and `numSccs` is the number of sccs
pair<vector<int>, int> getSCCs(const vector<vector<int>>& adj /*directed, unweighted graph*/) {
	int n = adj.size();
	vector<int> sccId(n);
	int numberOfSCCs = 0;
	stack<int> seen;
	{
		vector<bool> vis(n,false);
		auto dfs = [&](auto&& dfsPtr, int curr) -> void {
			vis[curr] = true;
			for(int x : adj[curr]) {
				if(!vis[x]) {
					dfsPtr(dfsPtr, x);
				}
			}
			seen.push(curr);
		};
		for(int i = 0; i < n; ++i) {
			if(!vis[i]) {
				dfs(dfs, i);
			}
		}
	}
	vector<vector<int>> adjInv(n);
	for(int i = 0; i < n; ++i) {
		for(int to : adj[i]) {
			adjInv[to].push_back(i);
		}
	}
	vector<bool> vis(n,false);
	auto dfs = [&](auto&& dfsPtr, int curr) -> void {
		vis[curr] = true;
		sccId[curr] = numberOfSCCs;
		for(int x : adjInv[curr]) {
			if(!vis[x]) {
				dfsPtr(dfsPtr, x);
			}
		}
	};
	while(!seen.empty()) {
		int node = seen.top();
		seen.pop();
		if(vis[node]) {
			continue;
		}
		dfs(dfs, node);
		numberOfSCCs++;
	}
	return make_pair(sccId, numberOfSCCs);
}
