#include "../../template.h"
#include "../test_utilities/generators/random.h"
#include "../test_utilities/generators/graphGen.h"

#include "../../../Library/graphs/dijkstra.h"
#include "../../../Library/graphs/floydWarshall.h"

int main() {
	for(int tests = 100; tests--;) {
		int n = getRand(1, 100);//nodes
		if(getRand(1,2) == 1) n = getRand(1, 10);

		cout << "n: " << n << endl;
		vector<vector<pair<int,long long>>> adj = convertAdjToWeighted(genRandomGraph(n, true /*isDirected*/, false /*isConnected*/, getRand(1,2) == 1/*isSimple*/));

		vector<vector<long long>> from_dijkstras(n);
		for(int i = 0; i < n; i++) {
			from_dijkstras[i] = dijkstra(adj, i).len;
		}
		assert(from_dijkstras == floydWarshall(adj));
	}

	cout << "Tests passed!" << endl;
	return 0;
}
