#include "../template.h"

#include "../../random.h"
#include "../../content/graphs/bridges_and_cuts.h"
#include "../../content/data_structures/disjointSet.h"

int main() {
	for(int tests = 20; tests--;) {
		int n = getRand(1, 1000);//nodes
		int m = getRand(1, 5000);//edges
		m = min(m, n * (n-1) / 2);
		vector<pair<int,int>> edges;
		{
			vector<pair<int,int>> allEdges;
			for(int i = 0; i < n; i++) {
				for(int j = i+1; j < n; j++) {
					allEdges.push_back({i,j});
				}
			}
			for(int i = 0, sz = (int)allEdges.size(); i < sz; i++) {
				swap(allEdges[i], allEdges[getRand(i, sz-1)]);
			}
			for(int i = 0; i < m; i++) {
				edges.push_back(allEdges[i]);
			}
		}

		vector<vector<int>> adj(n);
		for(auto [u,v] : edges) {
			adj[u].push_back(v);
			adj[v].push_back(u);
		}

		biconnected_components bcc(adj);

		disjointSet ds(n);
		for(auto [u,v] : edges) {
			ds.merge(u,v);
		}
		int numComponents = ds.numberOfSets;

		for(int i = 0; i < m; i++) {
			disjointSet curr(n);
			for(int j = 0; j < m; j++) {
				if(j == i) continue;
				auto [u,v] = edges[j];
				curr.merge(u,v);
			}
			//sanity check
			assert(curr.numberOfSets >= numComponents);
			bool isBridgeNaive = (curr.numberOfSets > numComponents);
			auto [u,v] = edges[i];
			assert(isBridgeNaive == bcc.is_bridge_edge(u,v));
		}
		cout << "is_bridge_edge passed" << endl;

		for(int i = 0; i < n; i++) {
			disjointSet curr(n);
			for(auto [u,v] : edges) {
				if(u == i || v == i) continue;
				curr.merge(u,v);
			}
			bool isCutNaive = false;
			if(!adj[i].empty()) {//nodes with 0 neighbors are **not** considered cut nodes
				//sanity check
				assert(curr.numberOfSets-1 >= numComponents);
				isCutNaive = (curr.numberOfSets-1 > numComponents);
			}
			assert(isCutNaive == bcc.is_cut[i]);
		}
		cout << "cut nodes passed" << endl;

	}

	cout << "Tests passed!" << endl;
	return 0;
}
