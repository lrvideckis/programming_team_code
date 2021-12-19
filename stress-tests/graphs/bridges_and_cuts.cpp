#include "../template.h"

#include "../../random.h"
#include "../../content/graphs/bridges_and_cuts.h"
#include "../../content/data_structures/disjointSet.h"

int main() {
	for(int tests = 1000; tests--;) {
		int n, m;
		set<pair<int,int>> edges;
		bool graphGenType1 = false;
		if(getRand(1,2) == 1) {//TODO: put back
			graphGenType1 = true;
			n = getRand(1, 1000);//nodes
			m = getRand(1, 5000);//edges
			m = min(m, n * (n-1) / 2);
			if(getRand(1,3) != 1) m /= 5;
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
		} else {//half the time, generate
			n = getRand(1, 1000);//nodes
			m = n-1;
			int extraEdges = getRand(0,30);
			extraEdges = min(extraEdges, n*(n-1)/2 - m);
			for(int i = 1; i < n; i++) {
				edges.insert({getRand(0, i-1), i});
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

		vector<vector<int>> adj(n);
		for(auto [u,v] : edges) {
			adj[u].push_back(v);
			adj[v].push_back(u);
		}

		biconnected_components bcc(adj);
		block_cut_tree bct(bcc);

		disjointSet ds(n);
		for(auto [u,v] : edges) {
			ds.merge(u,v);
		}
		int numComponents = ds.numberOfSets;

		for(auto &eTest : edges) {
			disjointSet curr(n);
			for(auto &e : edges) {
				if(e == eTest) continue;
				curr.merge(e.first,e.second);
			}
			//sanity check
			assert(curr.numberOfSets >= numComponents);
			bool isBridgeNaive = (curr.numberOfSets > numComponents);
			auto [u,v] = eTest;
			//cout << "bridge naive, fast: " << isBridgeNaive << " " << bcc.is_bridge_edge(u,v) << endl;
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

		for(int iter = 100; iter--;) {
			int node1 = getRand(0,n-1), node2 = getRand(0,n-1);
			bool sameBCCNaive = true;
			if(n == 2 && node1 != node2) sameBCCNaive = false;
			for(int i = 0; i < n; i++) {
				if(i == node1 || i == node2) continue;
				disjointSet curr(n);
				for(auto [u,v] : edges) {
					if(u == i || v == i) continue;
					curr.merge(u,v);
				}
				if(curr.find(node1) != curr.find(node2)) {
					sameBCCNaive = false;
					break;
				}
			}
			bool sameBBCMiddle = false;
			for(const vector<int>& currBcc : bcc.components) {
				if(find(currBcc.begin(), currBcc.end(), node1) != currBcc.end()) {
					if(find(currBcc.begin(), currBcc.end(), node2) != currBcc.end()) {
						sameBBCMiddle = true;
						break;
					}
				}
			}
			bool res = bct.same_biconnected_component(node1, node2);
			if(!(sameBCCNaive == res && res == sameBBCMiddle)) {
				cout << "graph gen type: " << graphGenType1 << endl;
				cout << "n: " << n << endl;
				cout << "edges: " << endl;
				for(auto [u,v] : edges) cout << u << " " << v << endl;
				cout << endl;
				cout << "components: " << endl;
				for(auto v : bcc.components) {
					for(auto e : v) cout << e << " ";
					cout << endl;
				}
				cout << endl;

				cout << "query nodes: " << node1 << " " << node2 << endl;
				cout << "naive, middle, fast: " << sameBCCNaive << " " << sameBBCMiddle << " " << res << endl;
				cout << flush;
				return 0;
			}
			assert(sameBCCNaive == res && res == sameBBCMiddle);
		}
		cout << "bct same bcc test passed" << endl;
	}

	cout << "Tests passed!" << endl;
	return 0;
}
