#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
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

#include "../../content/data_structures/disjointSet.h"

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
