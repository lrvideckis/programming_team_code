#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"
#include "../../template.h"

#include "../../../Library/graphs/hopcroftKarp.h"

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
	match res = hopcroftKarp(adj, r);
	cout << res.sizeOfMatching << endl;
	//asserting correctness of both ml, and mr (as well as printing answer)
	int sizeL = 0;
	for(int i = 0; i < l; i++) {
		if(res.ml[i] != -1) {
			sizeL++;
			int nodeR = res.ml[i];
			cout << i << " " << nodeR << endl;
			assert(res.mr[nodeR] == i);
		}
	}
	int sizeR = 0;
	for(int i = 0; i < r; i++) {
		if(res.mr[i] != -1) {
			sizeR++;
			int nodeL = res.mr[i];
			assert(res.ml[nodeL] == i);
		}
	}
	assert(sizeL == res.sizeOfMatching);
	assert(sizeR == res.sizeOfMatching);

	//asserting found min vertex cover is correct
	int cnt = 0;
	for(int i = 0; i < l; i++) cnt += res.leftMVC[i];
	for(int i = 0; i < r; i++) cnt += res.rightMVC[i];
	assert(cnt == res.sizeOfMatching);//size of min vertex cover == size of max matching
	for(auto [u,v] : edges) {
		assert(res.leftMVC[u] || res.rightMVC[v]);
	}
	return 0;
}
