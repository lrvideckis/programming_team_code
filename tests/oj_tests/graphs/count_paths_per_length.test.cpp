#define PROBLEM "https://judge.yosupo.jp/problem/frequency_table_of_tree_distance"
#include "../../../kactl/stress-tests/utilities/template.h"
#include "../../random.h"

#include "../../../library/graphs/count_paths_per_length.h"
#include "../../../library/graphs/count_paths_per_node.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	vector<vector<int>> adj(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector<long long> cnt_len = count_paths_per_length(adj);
	if (n >= 2) {
		int k = get_rand(1, n);
		long long sum = 0;
		for (long long num_paths : count_paths_per_node(adj, k))
			sum += num_paths;
		assert(sum % (k + 1) == 0);
		assert(sum / (k + 1) == cnt_len[k]);
	}
	for (int i = 1; i < n; i++)
		cout << cnt_len[i] << " ";
	cout << '\n';
	return 0;
}
