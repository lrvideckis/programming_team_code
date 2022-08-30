#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../../template.h"
#include "../../../kactl/stress-tests/utilities/genTree.h"
#include "../../../library/graphs/kth_node_on_path.h"

#include "../../../library/graphs/count_paths_per_node.h"

vector<vector<long long>> naive(const vector<vector<pair<int, long long>>>& adj_weighted) {
	int n = adj_weighted.size();
	kth_node_on_path path(adj_weighted, 0);
	vector<vector<long long>> cnts_naive(n + 1, vector<long long>(n, 0));
	for (int u = 0; u < n; u++) {
		for (int v = u; v < n; v++) {
			int path_length_edges = path.lca.dist_edges(u, v);
			for (int i = 0; i <= path_length_edges; i++)
				cnts_naive[path_length_edges][path.query(u, v, i)]++;
		}
	}
	return cnts_naive;
}

int main() {
	srand(time(NULL)); //since kactl's genRandomTree uses rand
	for (int n = 2; n <= 100; n++) {
		vector<vector<int>> adj(n);
		vector<vector<pair<int, long long>>> adj_weighted(n);
		for (auto [u, v] : genRandomTree(n)) {
			adj[u].push_back(v);
			adj[v].push_back(u);
			adj_weighted[u].emplace_back(v, 1LL);
			adj_weighted[v].emplace_back(u, 1LL);
		}
		vector<vector<long long>> cnts_naive = naive(adj_weighted);
		for (int k = 1; k <= n; k++)
			assert(count_paths_per_node(adj, k) == cnts_naive[k]);
	}
	cout << "Hello World\n";
	return 0;
}
