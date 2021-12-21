#include "../test_utilities/template.h"
#include "../test_utilities/random.h"
#include "../test_utilities/graphGen.h"

#include "../../content/graphs/scc.h"
#include "../../content/graphs/floydWarshall.h"

const ll inf = 1e18;//must match inf used in floyd

int main() {
	for(int tests = 1000; tests--;) {
		int n = getRand(1, 1000);//nodes
		if(getRand(1,2) == 1) n = getRand(1, 10);

		cout << "n: " << n << endl;
		vector<vector<int>> adj = genRandomGraph(n, true /*isDirected*/, false/*isConnected*/, getRand(1, 2) == 1/*isSimple*/);
		assert((int)adj.size() == n);

		vector<vector<pair<int,ll>>> adjW(n);
		for(int i = 0; i < n; i++) {
			for(int next : adj[i]) adjW[i].push_back({next,1});
		}

		vector<vector<ll>> lens = floydWarshall(adjW);

		scc sc(adj);
		for(int i = 0; i < n; i++) {
			for(int j = i; j < n; j++) {
				bool sameSCCFloyd = (lens[i][j] != inf && lens[j][i] != inf);
				bool sameSCC = (sc.getSccID(i) == sc.getSccID(j));
				assert(sameSCCFloyd == sameSCC);
			}
		}
	}

	cout << "Tests passed!" << endl;
	return 0;
}
