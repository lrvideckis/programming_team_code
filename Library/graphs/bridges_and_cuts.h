#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

struct bridge_and_cut {

	bridge_and_cut(const vector<vector<pair<int/*neighbor*/,int/*edge ID*/>>>& adj, int numEdges) :
		tin(adj.size(), 0),
		low(adj.size(), 0),
		timer(1),
		isCut(adj.size(), false),
		isBridge(numEdges, false) {
		for(int i = 0; i < (int)adj.size(); i++) {
			if(!tin[i])
				dfs(i, -1, adj);
		}
	}

	vector<int> tin, low;
	int timer;//, numCCs;
	vector<bool> isCut, isBridge;
	//stack<int> st;
	//vector<int> compId;

	void dfs(int v, int pId, const vector<vector<pair<int,int>>>& adj) {
		tin[v] = low[v] = timer++;
		int children = 0;
		//st.push(v);
		for (auto [to, eId] : adj[v]) {
			if (eId == pId) continue;
			if(tin[to]) {
				low[v] = min(low[v], tin[to]);
			} else {
				children++;
				dfs(to, eId, adj);
				if(pId != -1 && low[to] >= tin[v]) {
					isCut[v] = true;
				}
				if(low[to] > tin[v]) {
					isBridge[eId] = true;
				}
				low[v] = min(low[v], low[to]);
			}
		}
		if(pId == -1 && children > 1) {
			isCut[v] = true;
		}
		  /*
		if(tin[v] == low[v]) {
			int node;
			do {
				compId[node = st.top()] = numCCs;
				st.pop();
			} while(node != v);
			numCCs++;
		}
			*/
	}
};


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
	bridge_and_cut bac(adj, m);

	vector<pair<int,int>> bridges;
	for(int i = 0; i < m; i++) {
		if(bac.isBridge[i]) {
			bridges.push_back(edges[i]);
		}
	}
	if(bridges.empty()) {
		cout << "Sin bloqueos" << endl;
	} else {
		sort(bridges.begin(), bridges.end());
		cout << bridges.size() << endl;
		for(auto [u,v] : bridges) cout << u << " " << v << endl;
	}


	/*
	cout << bac.numCCs << endl;
	vector<vector<int>> comps(bac.numCCs);
	for(int i = 0; i < n; i++) {
		comps[bac.compId[i]].push_back(i);
	}
	for(const vector<int>& comp : comps) {
		cout << comp.size();
		for(int node : comp) cout << " " << node;
		cout << endl;
	}
	*/
	return 0;
}
