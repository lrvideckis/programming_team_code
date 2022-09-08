#define PROBLEM "https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification"
#include "../../template.hpp"

#include "../../../library/graphs/subtree_isomorphism_classification.hpp"

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
	auto buckets = subtree_isomorphism_classification(adj, 0);
	cout << buckets.k << '\n';
	for (auto a : buckets.ids)
		cout << a << ' ';
	cout << '\n';
	return 0;
}
