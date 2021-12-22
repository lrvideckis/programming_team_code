#include "../test_utilities/template.h"
#include "../test_utilities/random.h"
#include "../test_utilities/treeGen.h"

#include "../../content/graphs/lca.h"
#include "../../content/graphs/hld.h"
#include "../../content/data_structures/disjointSet.h"

void dfs(int node, int par, const vector<vector<pair<int, ll>>>& adjweighted, vector<int>& parent, vector<int>& depth, vector<ll>& pathWeight) {
	parent[node] = par;
	for(auto [child,weight] : adjweighted[node]) {
		if(child == par) continue;
		depth[child] = 1 + depth[node];
		pathWeight[child] = weight + pathWeight[node];
		dfs(child, node, adjweighted, parent, depth, pathWeight);
	}
}

int main() {
	for(int tests = 100; tests--;) {
		int n = getRand(1, 1000);//nodes
		if(getRand(1,2) == 1) n = getRand(1, 10);

		cout << "n: " << n << endl;
		vector<vector<pair<int, ll>>> adjweighted(n);
		vector<vector<int>> adj(n);
		{
			disjointSet ds(n);
			int numEdges = 0;
			for(auto [u,v] : genRandomTree(n)) {
				assert(ds.merge(u,v));
				numEdges++;
				ll weight = getRand(0, 1e9);
				adjweighted[u].push_back({v, weight});
				adjweighted[v].push_back({u, weight});
				adj[u].push_back(v);
				adj[v].push_back(u);
			}
			assert(numEdges == n-1);
		}
		int root = getRand(0, n-1);

		lca lc(adjweighted, root);
		hld hl(adj, root);

		vector<int> parent(n);
		vector<int> depth(n, 0);
		vector<ll> pathWeight(n, 0);
		dfs(root, root, adjweighted, parent, depth, pathWeight);

		for(int iter = 100; iter--;) {
			int node = getRand(0, n-1);
			int k = getRand(0, n/4);
			int kthParFast = lc.kthPar(node, k);
			while(k--) node = parent[node];
			assert(node == kthParFast);
		}

		for(int iter = 100; iter--;) {
			int x = getRand(0, n-1), y = getRand(0, n-1);
			int lcaFast = lc.getLca(x, y);
			int lcaFastFromHld = hl.lca(x, y);
			set<int> allAncestors;
			allAncestors.insert(x);
			while(x != root) {
				allAncestors.insert(x);
				x = parent[x];
				allAncestors.insert(x);
			}
			while(!allAncestors.count(y)) {
				y = parent[y];
			}
			assert(lcaFast == y);
			assert(lcaFast == lcaFastFromHld);
		}

		for(int iter = 100; iter--;) {
			int x = getRand(0, n-1), y = getRand(0, n-1);
			depth[x] = pathWeight[x] = 0;
			dfs(x, x, adjweighted, parent, depth, pathWeight);
			assert(lc.distEdges(x, y) == depth[y]);
			assert(lc.distWeight(x, y) == pathWeight[y]);

			set<int> nodesInPathFromHld;
			for(auto [lTime, rTime] : hl.path(x,y)) {
				for(int t = lTime; t <= rTime; t++) {
					int node = hl.timeInToNode[t];
					assert(!nodesInPathFromHld.count(node));
					nodesInPathFromHld.insert(node);
				}
			}

			set<int> nodesInPath;
			nodesInPath.insert(y);
			while(y != x) {
				y = parent[y];
				nodesInPath.insert(y);
			}

			assert(nodesInPathFromHld == nodesInPath);
		}
	}

	cout << "Tests passed!" << endl;
	return 0;
}
