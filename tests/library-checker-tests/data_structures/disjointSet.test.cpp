#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include "../../stress-tests/test_utilities/template.h"

#include "../../../Library/data_structures/disjointSet.h"

int main() {
	cin.tie(0)->sync_with_stdio(false);
	int n, q;
	cin >> n >> q;
	disjointSet ds(n);
	while(q--) {
		int t, u, v;
		cin >> t >> u >> v;
		if(t == 0) {
			ds.merge(u,v);
		} else {
			assert(t == 1);
			cout << (ds.find(u) == ds.find(v)) << endl;
		}
	}
	return 0;
}
