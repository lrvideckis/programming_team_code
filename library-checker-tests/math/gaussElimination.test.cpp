#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations"
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

#include "../../content/math/gaussElimination.h"


int main() {
	cin.tie(0)->sync_with_stdio(false);

	const int mod = 998244353;

	int n, m;
	cin >> n >> m;

	vector<vector<int>> A(n, vector<int>(m));
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			cin >> A[i][j];
		}
	}

	vector<int> b(n);
	for(int i = 0; i < n; i++) {
		cin >> b[i];
	}

	vector<vector<int>> x = solve_linear(A, b, mod);
	cout << (int)x.size() - 1 << endl;
	for (vector<int>& v : x) {
		for (int i = 0; i < m; ++i) {
			cout << v[i] << " ";
		}
		cout << endl;
	}
	return 0;
}
