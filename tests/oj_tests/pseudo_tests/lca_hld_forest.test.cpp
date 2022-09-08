#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../../../kactl/stress-tests/utilities/template.h"
#include "../../../kactl/content/data-structures/UnionFind.h"
#include "../../../kactl/content/graph/FloydWarshall.h"
#include "../../../library/misc/random.hpp"

#include "../../../library/graphs/lca.hpp"
#include "../../../library/graphs/hld.hpp"

int main() {
	for (int tests = 30; tests--;) {
		const int N = get_rand<int>(1, 100);
		vector<vector<int>> adj(N);
		vector<vector<long long>> matrix(N, vector<long long>(N, inf)), matrix_weighted(N, vector<long long>(N, inf));
		vector<vector<pair<int, long long>>> adj_weighted(N);
		UF uf(N);
		int edges = 0;
		for (int q = N; q--;) {
			int u = get_rand<int>(0, N);
			int v = get_rand<int>(0, N);
			if (u == v) continue;
			if (uf.join(u, v)) {
				auto w = get_rand<long long>(0, (long long)1e15);
				edges++;
				adj[u].push_back(v);
				adj[v].push_back(u);
				adj_weighted[u].emplace_back(v, w);
				adj_weighted[v].emplace_back(u, w);
				matrix[u][v] = 1;
				matrix[v][u] = 1;
				matrix_weighted[u][v] = w;
				matrix_weighted[v][u] = w;
			}
		}
		cerr << "edges added: " << edges << " number of nodes: " << N << endl;
		floydWarshall(matrix);
		floydWarshall(matrix_weighted);
		LCA lca(adj_weighted);
		HLD hld(adj);
		for (int u = 0; u < N; u++) {
			for (int v = 0; v < N; v++) {
				if (uf.sameSet(u, v)) {
					assert(lca.dist_weight(u, v) == matrix_weighted[u][v]);
					assert(lca.dist_edges(u, v) == matrix[u][v]);
					assert(lca.get_lca(u, v) == hld.lca(u, v));
					int len_nodes_path = 0;
					for (auto [l, r] : hld.path(u, v))
						len_nodes_path += r - l;
					assert(len_nodes_path - 1 == matrix[u][v]);
				}
			}
		}
	}
	cout << "Hello World\n";
	return 0;
}
