#include "test_utilities/template.h"
#include "test_utilities/random.h"
#include "test_utilities/graphGen.h"

#include "../../Library/graphs/dijkstra.h"
#include "../../Library/graphs/floydWarshall.h"

int main() {
	for(int tests = 1000; tests--;) {
		int n = getRand(1, 1000);//nodes
		if(getRand(1,2) == 1) n = getRand(1, 10);

		cout << "n: " << n << endl;
		vector<vector<pair<int,ll>>> adj = convertAdjToWeighted(genRandomGraph(n, true /*isDirected*/, false /*isConnected*/, getRand(1,2) == 1/*isSimple*/));

		vector<vector<ll>> from_dijkstras(n);
		for(int i = 0; i < n; i++) {
			from_dijkstras[i] = dijkstra(adj, i).len;
		}
		assert(from_dijkstras == floydWarshall(adj));
	}

	cout << "Tests passed!" << endl;
	return 0;
}
