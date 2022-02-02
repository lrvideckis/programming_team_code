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

	vector<vector<int>> matrix(n, vector<int>(m));
	for(int i= 0; i < n; i++) {
		for(int j= 0; j < m; j++) {
			cin >> matrix[i][j];
		}
	}


	for(int i= 0; i < n; i++) {
		int rhs;
		cin >> rhs;
		matrix[i].push_back(rhs);
	}

	matrixInfo info = gauss(matrix, mod);

	if(info.det == 0) {//no solution
		cout << -1 << endl;
		return 0;
	}

	for(int i = 0; i < min(info.rank, m); i++) {
		cout << matrix[i].back() << " ";
	}
	for(int i = min(info.rank, m); i < m; i++) {
		cout << 0 << " ";
	}
	cout << endl;

	for(int i = 0; i < info.rank; i++) {
		for(int j = 0; j < m; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}
