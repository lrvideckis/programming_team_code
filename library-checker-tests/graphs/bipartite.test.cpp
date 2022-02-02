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

#include "../../content/graphs/bipartite.h"

int main() {
	cin.tie(0)->sync_with_stdio(false);
	int l, r, m;
	cin >> l >> r >> m;
	BipartiteMatcher bm(l, r);
	while(m--) {
		int u, v;
		cin >> u >> v;
		bm.AddEdge(u, v);
	}
	cout << bm.Solve() << endl;
	for(int i = 0; i < l; i++) {
		if(bm.L[i] != -1) {
			cout << i << " " << bm.L[i] << endl;
		}
	}
	return 0;
}
