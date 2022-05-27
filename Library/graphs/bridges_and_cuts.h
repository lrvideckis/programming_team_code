#pragma once
//library checker tests: https://judge.yosupo.jp/problem/biconnected_components, https://judge.yosupo.jp/problem/two_edge_connected_components
//with asserts checking correctness of isBridge and isCut

//O(n+m) time & space
//2 edge cc and bcc stuff doesn't depend on each other, so delete whatever is not needed

//To initialize `adj`:
//eid = 0
//for each edge (a,b):
//	adj[a].emplace_back(b, eid);
//	adj[b].emplace_back(a, eid++);

struct info {
	//2 edge connected component stuff (e.g. components split by bridge edges) https://cp-algorithms.com/graph/bridge-searching.html
	int num2EdgeCCs;
	vector<bool> isBridge;//edge id -> true iff bridge edge
	vector<int> TwoEdgeCCID;//node -> ID of 2-edge component (which are labeled 0, 1, ..., `num2EdgeCCs`-1)

	//bi-connected component stuff (e.g. components split by cut/articulation nodes) https://cp-algorithms.com/graph/cutpoints.html
	int numBCCs;
	vector<bool> isCut;//node -> true iff cut node
	vector<int> bccID;//edge id -> ID of BCC (which are labeled 0, 1, ..., `numBCCs`-1)
};

info bridge_and_cut(const vector<vector<pair<int/*neighbor*/, int/*edge id*/>>>& adj/*undirected graph*/, int m/*number of edges*/) {
	//stuff for both (always keep)
	int n = adj.size(), timer = 1;
	vector<int> tin(n, 0), low(n, 0);
	//2 edge CC stuff (delete if not needed)
	int num2EdgeCCs = 0;
	vector<bool> isBridge(m, false);
	vector<int> TwoEdgeCCID(n), nodeStack;
	//BCC stuff (delete if not needed)
	int numBCCs = 0;
	vector<bool> isCut(n, false);
	vector<int> bccID(m), edgeStack;
	auto dfs = [&](auto&& self, int v, int pId) -> void {
		tin[v] = low[v] = timer++;
		int deg = 0;
		nodeStack.push_back(v);
		for (auto [to, eId] : adj[v]) {
			if (eId == pId) continue;
			if (!tin[to]) {
				edgeStack.push_back(eId);
				self(self, to, eId);
				if (low[to] >= tin[v]) {
					isCut[v] = true;
					while (true) {
						int edge = edgeStack.back();
						edgeStack.pop_back();
						bccID[edge] = numBCCs;
						if (edge == eId) break;
					}
					numBCCs++;
				}
				low[v] = min(low[v], low[to]);
				deg++;
			} else if (tin[to] < tin[v]) {
				edgeStack.push_back(eId);
				low[v] = min(low[v], tin[to]);
			}
		}
		if (pId == -1) isCut[v] = (deg > 1);
		if (tin[v] == low[v]) {
			if (pId != -1) isBridge[pId] = true;
			while (true) {
				int node = nodeStack.back();
				nodeStack.pop_back();
				TwoEdgeCCID[node] = num2EdgeCCs;
				if (node == v) break;
			}
			num2EdgeCCs++;
		}
	};
	for (int i = 0; i < n; i++) {
		if (!tin[i])
			dfs(dfs, i, -1);
	}
	return {num2EdgeCCs, isBridge, TwoEdgeCCID, numBCCs, isCut, bccID};
}
