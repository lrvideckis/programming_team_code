#pragma once

//status: tested against floyd warshals on random graphs. also tested on https://judge.yosupo.jp/problem/scc

struct sccInfo {
	//sccId[i] is the id of the scc containing node `i`
	vector<int> sccId;
	//scc's are labeled 0,1,...,`numberOfSCCs-1`
	int numberOfSCCs;
	//adjacency list of "condensation graph", condensation graph is a dag with topo ordering 0,1,...,`numberOfSCCs-1`
	//  - nodes are scc's (labeled by sccId)
	//  - edges: if u -> v exists in original graph, then add edge sccId[u] -> sccId[v] (then remove multiple&self edges)
	vector<vector<int>> adj;
};

sccInfo getSCCs(const vector<vector<int>>& adj /*directed, unweighted graph*/) {
	int n = adj.size();
	sccInfo res;
	res.sccId.resize(n);
	res.numberOfSCCs = 0;
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
		res.sccId[curr] = res.numberOfSCCs;
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
		res.numberOfSCCs++;
	}
	res.adj.resize(res.numberOfSCCs);
	for(int i = 0; i < n; i++) {
		for(int j : adj[i]) {
			int sccI = res.sccId[i], sccJ = res.sccId[j];
			if(sccI != sccJ) {
				assert(sccI < sccJ);//sanity check for topo order
				res.adj[sccI].push_back(sccJ);
			}
		}
	}
	for(vector<int>& nexts : res.adj) {
		sort(nexts.begin(), nexts.end());
		nexts.erase(unique(nexts.begin(), nexts.end()), nexts.end());
	}
	return res;
}
