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

#include "../test_utilities/random.h"
#include "../../content/range_data_structures/distinct_query.h"

int main() {
	cin.tie(0)->sync_with_stdio(false);
	for(int tests = 5; tests--;) {
		int n = getRand(1, 100);
		vector<int> arr(n);
		for(int i = 0; i < n; i++) {
			arr[i] = getRand(0, 1e9);
		}
		persistentSegTree pst(arr);
		for(int l = 0; l < n; l++) {
			for(int r = l; r < n; r++) {
				set<int> copyArr(arr.begin() + l, arr.begin() + r + 1);
				assert(pst.query(l, r) == (int)copyArr.size());
			}
		}
	}
	return 0;
}
