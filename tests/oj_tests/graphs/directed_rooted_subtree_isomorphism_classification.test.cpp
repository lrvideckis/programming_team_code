#define PROBLEM "https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification"
#include "../../template.h"

#include "../../../library/graphs/rooted_subtree_isomorphism_classification.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	vector<vector<int>> adj(n);
	for (int i = 1; i < n; i++) {
		int p;
		cin >> p;
		adj[p].push_back(i);
	}
	auto buckets = rooted_subtree_isomorphism_classification(adj, 0);
	cout << buckets.k << '\n';
	for (auto a : buckets.ids)
		cout << a << ' ';
	cout << '\n';
	return 0;
}
