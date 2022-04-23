#define PROBLEM "https://judge.yosupo.jp/problem/lca"
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
typedef long long ll;

#include "../../content/graphs/lca.h"

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,q;
	cin >> n >> q;
	vector<vector<pair<int,ll>>> adj(n);
	for(int i = 1; i < n; ++i) {
		int par;
		cin >> par;
		adj[par].push_back({i,1LL});
		adj[i].push_back({par,1LL});
	}
	lca h(adj,0);
	while(q--) {
		int u,v;
		cin >> u >> v;
		cout << h.getLca(u,v) << endl;
	}
}
