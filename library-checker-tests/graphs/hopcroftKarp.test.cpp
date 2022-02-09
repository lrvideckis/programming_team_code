#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
#include <climits>
#include <memory>
using namespace std;
#define endl '\n'

#include "../../content/graphs/hopcroftKarp.h"

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
	cout << res.matching.size() << endl;
	for(auto [u,v] : res.matching) {
		cout << u << " " << v << endl;
	}

	//asserting found min vertex cover is correct
	int cnt = 0;
	for(int i = 0; i < l; i++) cnt += res.leftMVC[i];
	for(int i = 0; i < r; i++) cnt += res.rightMVC[i];
	assert(cnt == (int)res.matching.size());//size of min vertex cover == size of max matching
	for(auto [u,v] : edges) {
		assert(res.leftMVC[u] || res.rightMVC[v]);
	}
	return 0;
}
