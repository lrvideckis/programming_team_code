#include "../test_utilities/template.h"
#include "../test_utilities/random.h"
#include "../test_utilities/treeGen.h"

#include "../../content/graphs/dijkstra.h"
#include "../../content/graphs/floydWarshall.h"

int main() {
	for(int tests = 1000; tests--;) {
		int n;
		set<pair<int,int>> edges;
		bool graphGenType1 = false;
		if(getRand(1,2) == 1) {
			graphGenType1 = true;
			n = getRand(1, 1000);//nodes
			if(getRand(1,2) == 1) n = getRand(1, 6);
			int m = getRand(0, min(5000, n * (n-1) / 2));//edges
			if(n > 6 && getRand(1,3) != 1) m /= 5;
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
					edges.insert(allEdges[i]);
				}
			}
		} else {//half the time, generate trees with extra edges
			n = getRand(1, 1000);//nodes
			int m = n-1;
			int extraEdges = getRand(0,30);
			extraEdges = min(extraEdges, n*(n-1)/2 - m);

			for(auto [u,v] : genRandomTree(n)) {
				if(u > v) swap(u,v);
				edges.insert({u,v});
			}
			for(int i = 0; i < extraEdges; i++) {
				pair<int, int> currEdge;
				while(true) {
					currEdge = {getRand(0, n-1), getRand(0, n-1)};
					if(currEdge.first == currEdge.second) continue;
					if(currEdge.first > currEdge.second) swap(currEdge.first, currEdge.second);
					if(!edges.count(currEdge)) break;
				}
				edges.insert(currEdge);
			}
			assert((int)edges.size() == m + extraEdges);
		}
		cout << "# nodes, edges: " << n << " " << edges.size() << endl;

		vector<vector<pair<int,ll>>> adj(n);
		for(auto [u,v] : edges) {
			if(getRand(1, 3) > 1) {//directed edge
				adj[u].push_back({v, getRand(0, 1e9)});
			} else {//undirected edge
				adj[u].push_back({v, getRand(0, 1e9)});
				adj[v].push_back({u, getRand(0, 1e9)});
			}
		}

		vector<vector<ll>> from_dijkstras(n);
		for(int i = 0; i < n; i++) {
			from_dijkstras[i] = dijkstra(adj, i);
		}
		assert(from_dijkstras == floydWarshall(adj));
	}

	cout << "Tests passed!" << endl;
	return 0;
}
