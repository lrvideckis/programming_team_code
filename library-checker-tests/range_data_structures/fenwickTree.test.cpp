#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
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

#include "../../content/range_data_structures/fenwickTree.h"

int main() {
	cin.tie(0)->sync_with_stdio(false);
	int n,q;
	cin >> n >> q;
	vector<ll> arr(n);
	for(int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	fenwickTree<ll> ft(arr);
	while(q--) {
		int type;
		cin >> type;
		if(type == 0) {
			int p, x;
			cin >> p >> x;
			ft.update(p,x);
		} else {
			int l,r;
			cin >> l >> r;
			cout << ft.sum(l,r-1) << endl;
		}
	}
	return 0;
}
