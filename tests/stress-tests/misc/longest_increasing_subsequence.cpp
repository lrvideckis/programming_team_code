#include "../../template.h"
#include "../../../Library/misc/random.h"

#include "../../../Library/misc/longest_increasing_subsequence.h"

int main() {
	for(int tests = 500; tests--;) {

		int n = getRand(0,100);//TODO: change lower bound to 0
		vector<int> arr(n);
		for(int i = 0; i < n; i++) {
			arr[i] = getRand(-10,10);
		}

		vector<int> lis_idx = lis(arr);

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

	cout << "Tests passed!" << endl;
	return 0;
}
