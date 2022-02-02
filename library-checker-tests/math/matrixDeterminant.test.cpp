#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"
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

int main() {
	cin.tie(0)->sync_with_stdio(false);

	const int mod = 998244353;

	int n;
	cin >> n;

	vector<vector<int>> matrix(n, vector<int>(n));
	for(int i= 0; i < n; i++) {
		for(int j= 0; j < n; j++) {
			cin >> matrix[i][j];
		}
	}

	vector<int> b(n);
	matrixInfo info = solve_linear(matrix, b, mod);

	cout << info.det << endl;
	return 0;
}
