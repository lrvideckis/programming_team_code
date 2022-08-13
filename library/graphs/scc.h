#pragma once
//source: https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/SCC.h
//mnemonic: Strongly Connected Component
struct scc_info {
	int num_sccs;
	//scc's are labeled 0,1,...,`num_sccs-1`
	//scc_id[i] is the id of the scc containing node `i`
	//for each edge i -> j: scc_id[i] >= scc_id[j] (topo order of scc's)
	vector<int> scc_id;
};
//NOLINTNEXTLINE(readability-identifier-naming)
scc_info SCC(const vector<vector<int>>& adj /*directed, unweighted graph*/) {
	int n = adj.size(), timer = 1, num_sccs = 0;
	vector<int> tin(n, 0), scc_id(n, -1), node_stack;
	auto dfs = [&](auto self, int v) -> int {
		int low = tin[v] = timer++;
		node_stack.push_back(v);
		for (int to : adj[v]) {
			if (scc_id[to] < 0)
				low = min(low, tin[to] ? tin[to] : self(self, to));
		}
		if (tin[v] == low) {
			while (node != v) {
				int node = node_stack.back();
				node_stack.pop_back();
				scc_id[node] = num_sccs;
			}
			num_sccs++;
		}
		return low;
	};
	for (int i = 0; i < n; i++) {
		if (!tin[i])
			dfs(dfs, i);
	}
	return {num_sccs, scc_id};
}
