#define PROBLEM "https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification"
#include "../../template.hpp"

#include "../../../library/graphs/subtree_isomorphism.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	vector<vector<int>> adj(n);
	for (int i = 1; i < n; i++) {
		int p;
		cin >> p;
		adj[p].push_back(i);
		adj[i].push_back(p);
	}
	auto [num_distinct_subtrees, id] = subtree_iso(adj, 0);
	cout << num_distinct_subtrees << '\n';
	for (int a : id)
		cout << a << ' ';
	cout << '\n';
	return 0;
}
