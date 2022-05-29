#pragma once
//library checker tests: https://judge.yosupo.jp/problem/scc

struct sccInfo {
	int numSCCs;
	//scc's are labeled 0,1,...,`numSCCs-1`
	//sccId[i] is the id of the scc containing node `i`
	//for each edge i -> j: sccId[i] >= sccId[j]
	vector<int> sccId;
};

sccInfo getSCCs(const vector<vector<int>>& adj /*directed, unweighted graph*/) {
	int n = adj.size(), timer = 1, numSCCs = 0;
	vector<int> tin(n, 0), sccId(n, -1), nodeStack;
	auto dfs = [&](auto&& self, int v) -> int {
		int low = tin[v] = timer++;
		nodeStack.push_back(v);
		for (int to : adj[v]) {
			if (sccId[to] < 0)
				low = min(low, tin[to] ? tin[to] : self(self, to));
		}
		if (tin[v] == low) {
			while (true) {
				int node = nodeStack.back();
				nodeStack.pop_back();
				sccId[node] = numSCCs;
				if (node == v) break;
			}
			numSCCs++;
		}
		return low;
	};
	for (int i = 0; i < n; i++) {
		if (!tin[i])
			dfs(dfs, i);
	}
	return {numSCCs, sccId};
}
