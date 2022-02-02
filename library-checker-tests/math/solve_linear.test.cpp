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

#include "../../content/math/solve_linear.h"

//assumes A is row reduced already
vector<vector<int>> kernel( vector<vector<int>> A, int rank, int mod ) {
	int m = A[0].size();
	vector<vector<int>> res;
	vector<int> pivot(m, -1);
	for (int i = 0, j = 0; i < rank; ++i) {
		while (A[i][j] == 0) ++j;
		pivot[j] = i;
	}
	for (int j = 0; j < m; ++j) if (pivot[j] == -1) {
		vector<int> x(m, 0);
		x[j] = mod-1;
		for (int k = 0; k < j; ++k) if (pivot[k] != -1) x[k] = A[pivot[k]][j];
		res.push_back(x);
	}
	return res;
}

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

	matrixInfo info = solve_linear(A, b, mod);

	if(info.x.empty()) {
		cout << -1 << endl;
		return 0;
	}

	vector<vector<int>> ker = kernel(A, info.rank, mod);
	cout << (int)ker.size() << endl;

	for(int val : info.x) cout << val << " ";
	cout << endl;

	for (vector<int>& v : ker) {
		for (int i = 0; i < m; ++i) {
			cout << v[i] << " ";
		}
		cout << endl;
	}
	return 0;
}
