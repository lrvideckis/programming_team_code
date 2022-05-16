#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

struct info {
	int num2EdgeCCs, numBCCs;
	vector<bool> isBridge, isCut;
	vector<int> edgeCC, nodeCC;
};

info bridge_and_cut(const vector<vector<pair<int,int>>>& adj, int numEdges) {

	int n = adj.size(), timer = 1, numCCs = 0;
	vector<int> tin(n, 0), low(n, 0);
	vector<bool> isCut(n, false), isBridge(numEdges);

	auto dfs = [&](auto&& dfs, int v, int pId) -> void {
		tin[v] = low[v] = timer++;
		int children = 0;
		for (auto [to, eId] : adj[v]) {
			if (eId == pId) continue;
			if (tin[to]) {
				low[v] = min(low[v], tin[to]);
			} else {
				children++;
				dfs(dfs, to, v);
				if(pId != -1 && low[to] >= tin[v]) isCut[v] = true;
				isBridge[eId] = (low[to] > tin[v]);
				low[v] = min(low[v], low[to]);
			}
		}
		if(pId == -1)
			isCut[v] = (children > 1);

		if(tin[v] == low[v]) {
			while(true) {
				int node = st.top();
				st.pop();
				compId[node] = numCCs;
				if(node == v) break;
			}
			numCCs++;
		}
	};

	for(int i = 0; i < n; i++) {
		if(!tin[i])
			dfs(dfs, i, -1);
	}
	return {isCut};


}
//stack<int> st;
//vector<int> compId;




/*
 * requirements:
 * - finds both bridges and cut points in single DFS
 * - O(v+e), aka no sort to remove duplicates
 *
 * questions:
 * - struct or function with lambda dfs?
 *
 * */

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	vector<vector<pair<int,int>>> adj(n);
	vector<pair<int,int>> edges(m);
	for(int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].emplace_back(v, i);
		adj[v].emplace_back(u, i);

		if(u > v) swap(u,v);
		edges[i] = {u,v};
	}

	info bac = bridge_and_cut(adj);

	return 0;
}
