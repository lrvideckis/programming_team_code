#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../kactl_macros.hpp"
#include "../../../kactl/content/data-structures/UnionFind.h"
#include "../../../library/graphs/kth_node_on_path.hpp"
#include "../../../library/misc/random.hpp"

#include "../../../library/graphs/count_paths_per_node.hpp"
#include "../../../library/graphs/count_paths_per_length.hpp"

vector<vector<long long>> naive(const vector<vector<pair<int, long long>>>& adj_weighted, UF& uf) {
	int n = adj_weighted.size();
	kth_node_on_path path(adj_weighted);
	vector<vector<long long>> cnts_naive(n + 1, vector<long long>(n, 0));
	for (int u = 0; u < n; u++) {
		for (int v = u; v < n; v++) {
			if (uf.sameSet(u, v)) {
				int path_length_edges = path.lca.dist_edges(u, v);
				for (int i = 0; i <= path_length_edges; i++)
					cnts_naive[path_length_edges][path.query(u, v, i)]++;
			}
		}
	}
	return cnts_naive;
}

int main() {
	for (int n = 2; n <= 100; n++) {
		vector<vector<int>> adj(n);
		vector<vector<pair<int, long long>>> adj_weighted(n);
		UF uf(n);
		for (int q = n; q--;) {
			int u = get_rand<int>(0, n);
			int v = get_rand<int>(0, n);
			if (u == v) continue;
			if (uf.join(u, v)) {
				adj[u].push_back(v);
				adj[v].push_back(u);
				adj_weighted[u].emplace_back(v, 1LL);
				adj_weighted[v].emplace_back(u, 1LL);
			}
		}
		vector<vector<long long>> cnts_naive = naive(adj_weighted, uf);
		for (int k = 1; k <= n; k++)
			assert(count_paths_per_node(adj, k) == cnts_naive[k]);
		vector<long long> num_paths_len = count_paths_per_length(adj);
		for (int k = 1; k < n; k++) {
			vector<long long> count_paths = count_paths_per_node(adj, k);
			long long total_paths = accumulate(count_paths.begin(), count_paths.end(), 0LL);
			assert(total_paths % (k + 1) == 0);
			total_paths /= k + 1;
			assert(num_paths_len[k] == total_paths);
		}
	}
	cout << "Hello World\n";
	return 0;
}
