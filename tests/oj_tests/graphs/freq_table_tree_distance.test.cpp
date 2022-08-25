#define PROBLEM "https://judge.yosupo.jp/problem/frequency_table_of_tree_distance"
#include "../../../kactl/stress-tests/utilities/template.h"
#include "../../random.h"

#include "../../../library/graphs/tree_freq_dist.h"
#include "../../../library/graphs/k_len_path_node_count.h"

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
	vector<long long> cnt_len = tree_freq_dist(adj);
	{
		int k = get_rand(2, max(3, n + 1));
		long long sum = 0;
		for (long long num_paths : get_num_paths(adj, k))
			sum += num_paths;
		assert(sum % k == 0);
		assert(sum / k == cnt_len[k - 1]);
	}
	for (int i = 1; i < n; i++)
		cout << cnt_len[i] << " ";
	cout << '\n';
	return 0;
}
