#include "../../template.h"
#include "../test_utilities/generators/random.h"
#include "../test_utilities/generators/treeGen.h"
#include "../test_utilities/generators/graphGen.h"

#include "../../../Library/graphs/bridges_and_cuts.h"
#include "../../../Library/graphs/disjointSet.h"

int main() {
	for(int tests = 10; tests--;) {
		int n = getRand(1, 100);//nodes
		if(getRand(1,2) == 1) n = getRand(1, 6);

		cout << "n: " << n << flush;
		vector<vector<int>> adj = genRandomGraph(n, false /*isDirected*/, getRand(1,5) == 1 /*isConnected*/, true /*isSimple*/);

		biconnected_components bcc(adj);
		block_cut_tree bct(bcc);

		set<pair<int,int>> edges;
		for(int i = 0; i < n; i++) {
			for(int next : adj[i]) {
				assert(i != next);
				if(next <= i)
					edges.insert({next, i});
			}
		}


		disjointSet ds(n);
		for(auto [u,v] : edges) ds.merge(u,v);

		int numComponents = ds.numSets;

		for(auto &eTest : edges) {
			disjointSet curr(n);
			for(auto &e : edges) {
				if(e == eTest) continue;
				curr.merge(e.first,e.second);
			}
			//sanity check
			assert(curr.numSets >= numComponents);
			bool isBridgeNaive = (curr.numSets > numComponents);
			auto [u,v] = eTest;
			assert(isBridgeNaive == bcc.is_bridge_edge(u,v));
		}
		cout << "is_bridge_edge passed " << flush;

		for(int i = 0; i < n; i++) {
			disjointSet curr(n);
			for(auto [u,v] : edges) {
				if(u == i || v == i) continue;
				curr.merge(u,v);
			}
			bool isCutNaive = false;
			if(!adj[i].empty()) {//nodes with 0 neighbors are **not** considered cut nodes
				//sanity check
				assert(curr.numSets-1 >= numComponents);
				isCutNaive = (curr.numSets-1 > numComponents);
			}
			assert(isCutNaive == bcc.is_cut[i]);
		}
		cout << "cut nodes passed " << flush;

		for(int iter = 100; iter--;) {
			int node1 = getRand(0,n-1), node2 = getRand(0,n-1);
			if(node1 == node2) continue;
			bool sameBCCNaive = true;
			if(n == 2) {
				sameBCCNaive = (node1 == node2 || edges.size() == 1);
				assert(edges.size() <= 1);
				if(edges.size() == 1) assert(edges.count({0,1}));
			}
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
			int whichBcc = -1;
			for(int i = 0; i < (int)bcc.components.size(); i++) {
				vector<int>& currBcc = bcc.components[i];
				if(find(currBcc.begin(), currBcc.end(), node1) != currBcc.end()) {
					if(find(currBcc.begin(), currBcc.end(), node2) != currBcc.end()) {
						sameBBCMiddle = true;
						assert(whichBcc == -1);
						whichBcc = i;
					}
				}
			}
			int res = bct.which_bcc(node1, node2);
			if(!(sameBCCNaive == sameBBCMiddle && (res != -1) == sameBBCMiddle && res == whichBcc)) {
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
				cout << "naive, middle, fast, which_bcc_naive: " << sameBCCNaive << " " << sameBBCMiddle << " " << res << " " << whichBcc << endl;
				cout << flush;
				return 1;//test failed
			}

			//sanity check
			assert(sameBCCNaive == sameBBCMiddle);
			assert((res != -1) == sameBBCMiddle);
			assert(res == whichBcc);
		}
		cout << "bct same bcc test passed" << endl << flush;
	}

	cout << "Tests passed!" << endl;
	return 0;
}
