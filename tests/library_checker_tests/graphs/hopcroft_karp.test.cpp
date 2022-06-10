#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"
#include "../../template.h"

#include "../../../library/graphs/hopcroft_karp.h"

int main() {
	cin.tie(0)->sync_with_stdio(false);
	int l, r, m;
	cin >> l >> r >> m;
	vector<vector<int>> adj(l);
	vector<pair<int,int>> edges;
	while(m--) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		edges.push_back({u,v});
	}
	match res = hopcroft_karp(adj, r);
	cout << res.size_of_matching << endl;
	//asserting correctness of both match_l, and match_r (as well as printing answer)
	int sizeL = 0;
	for(int i = 0; i < l; i++) {
		if(res.match_l[i] != -1) {
			sizeL++;
			int nodeR = res.match_l[i];
			cout << i << " " << nodeR << endl;
			assert(res.match_r[nodeR] == i);
		}
	}
	int sizeR = 0;
	for(int i = 0; i < r; i++) {
		if(res.match_r[i] != -1) {
			sizeR++;
			int nodeL = res.match_r[i];
			assert(res.match_l[nodeL] == i);
		}
	}
	assert(sizeL == res.size_of_matching);
	assert(sizeR == res.size_of_matching);

	//asserting found min vertex cover is correct
	int cnt = 0;
	for(int i = 0; i < l; i++) cnt += res.mvc_l[i];
	for(int i = 0; i < r; i++) cnt += res.mvc_r[i];
	assert(cnt == res.size_of_matching);//size of min vertex cover == size of max matching
	for(auto [u,v] : edges) {
		assert(res.mvc_l[u] || res.mvc_r[v]);
	}
	return 0;
}
