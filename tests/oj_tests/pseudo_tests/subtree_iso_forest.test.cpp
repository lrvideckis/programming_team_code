#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../../../kactl/stress-tests/utilities/template.h"
#include "../../../kactl/content/data-structures/UnionFind.h"
#include "../../../library/misc/random.hpp"

#include "../../../library/graphs/subtree_isomorphism.hpp"

int main() {
	for (int n = 2; n <= 100; n++) {
		vector<vector<int>> adj(n);
		UF uf(n);
		for (int q = n; q--;) {
			int u = get_rand<int>(0, n);
			int v = get_rand<int>(0, n);
			if (u == v) continue;
			if (uf.join(u, v)) {
				adj[u].push_back(v);
				adj[v].push_back(u);
			}
		}
	}
	cout << "Hello World\n";
	return 0;
}
