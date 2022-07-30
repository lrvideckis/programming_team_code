#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include "../../template.h"

#include "../../../library/misc/dsu.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	DSU ds(n);
	while(q--) {
		int t, u, v;
		cin >> t >> u >> v;
		if(t == 0) {
			ds.join(u,v);
		} else {
			assert(t == 1);
			cout << (ds.find(u) == ds.find(v)) << endl;
		}
	}
	return 0;
}
