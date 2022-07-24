#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "../../template.h"
#include "../../random.h"

#include "../../../library/misc/lis.h"

int main() {
	for(int tests = 500; tests--;) {

		int n = get_rand(0,100);
		vector<int> arr(n);
		for(int i = 0; i < n; i++) {
			arr[i] = get_rand(-10,10);
		}

		vector<int> lis_idx = LIS(arr);

		if(n == 0) {
			assert(lis_idx.empty());
			continue;
		}

		vector<int> dp(n, 1);
		int max_dp = 0;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < i; j++) {
				if(arr[i] > arr[j]) {
					dp[i] = max(dp[i], 1 + dp[j]);
				}
			}
			max_dp = max(max_dp, dp[i]);
		}
		assert((int)lis_idx.size() == max_dp);
		for(int i = 1; i < (int)lis_idx.size(); i++) {
			assert(arr[lis_idx[i-1]] < arr[lis_idx[i]]);
		}
	}

	int a, b;
	cin >> a >> b;
	cout << a + b << endl;
	return 0;
}
