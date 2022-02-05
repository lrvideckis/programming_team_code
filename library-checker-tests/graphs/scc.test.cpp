#define PROBLEM "https://judge.yosupo.jp/problem/scc"
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

#include "../../content/graphs/scc.h"

int main() {
	cin.tie(0)->sync_with_stdio(false);
	int n,m;
	cin >> n >> m;
	vector<vector<int>> adj(n);
	for(int i = 0; i < m; i++) {
		int u,v;
		cin >> u >> v;
		adj[u].push_back(v);
	}
	sccInfo info = getSCCs(adj);
	cout << info.numberOfSCCs << endl;
	vector<vector<int>> eachScc(info.numberOfSCCs);
	for(int i = 0; i < n; i++) {
		eachScc[info.sccId[i]].push_back(i);
	}
	for(int i = 0; i < info.numberOfSCCs; i++) {
		cout << eachScc[i].size() << " ";
		for(int node : eachScc[i]) cout << node << " ";
		cout << endl;
	}
	return 0;
}
