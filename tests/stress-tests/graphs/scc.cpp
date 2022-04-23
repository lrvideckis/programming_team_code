#include "test_utilities/template.h"
#include "test_utilities/random.h"
#include "test_utilities/graphGen.h"

#include "../../Library/graphs/scc.h"
#include "../../Library/graphs/floydWarshall.h"

const ll inf = 1e18;//must match inf used in floyd

int main() {
	for(int tests = 1000; tests--;) {
		int n = getRand(1, 1000);//nodes
		if(getRand(1,2) == 1) n = getRand(1, 10);

		cout << "n: " << n << endl;
		vector<vector<int>> adj = genRandomGraph(n, true /*isDirected*/, false/*isConnected*/, getRand(1, 2) == 1/*isSimple*/);
		auto adjW = convertAdjToWeighted(adj);
		assert((int)adj.size() == n && (int)adjW.size() == n);

		vector<vector<ll>> lens = floydWarshall(adjW);

		sccInfo scc = getSCCs(adj);
		assert((int)scc.adj.size() == scc.numberOfSCCs);
		for(int i = 0; i < n; i++) {
			for(int j = i; j < n; j++) {
				bool sameSCCFloyd = (lens[i][j] != inf && lens[j][i] != inf);
				bool sameSCC = (scc.sccId[i] == scc.sccId[j]);
				assert(sameSCCFloyd == sameSCC);
			}
		}
	}

	cout << "Tests passed!" << endl;
	return 0;
}
