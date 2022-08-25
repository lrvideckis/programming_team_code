#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../../template.h"
#include "../../random.h"
#include "../../../kactl/stress-tests/utilities/genTree.h"
#include "../../../library/graphs/kth_node_on_path.h"

#include "../../../library/graphs/k_len_path_node_count.h"

vector<long long> naive(const vector<vector<pair<int, long long>>>& adj_weighted, int k) {
	int n = adj_weighted.size();
	kth_node_on_path path(adj_weighted, 0);
	vector<long long> cnts_naive(n, 0);
	for (int u = 0; u < n; u++) {
		for (int v = u + 1; v < n; v++) {
			int path_len_nodes = path.lca.dist_edges(u, v) + 1;
			if (path_len_nodes == k) {
				for (int i = 0; i < path_len_nodes; i++)
					cnts_naive[path.query(u, v, i)]++;
			}
		}
	}
	return cnts_naive;
}

int main() {
	for (int n = 2; n <= 100; n++) {
		vector<vector<int>> adj(n);
		vector<vector<pair<int, long long>>> adj_weighted(n);
		for (auto [u, v] : genRandomTree(n)) {
			adj[u].push_back(v);
			adj[v].push_back(u);
			adj_weighted[u].emplace_back(v, 1LL);
			adj_weighted[v].emplace_back(u, 1LL);
		}
		int k = get_rand(1, n + 1);
		assert(get_num_paths(adj, k) == naive(adj_weighted, k));
	}
	cout << "Hello World\n";
	return 0;
}
